cmake_minimum_required(VERSION 3.20)

project(
    BlockBreaker3D
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BLOCKBREAKER3D_ENABLE_AUDIO "Enable irrKlang audio support" ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(IRRKLANG_ROOT "" CACHE PATH "Path to the irrKlang SDK (set if not auto-detected)")

# --- Audio dependency discovery ------------------------------------------------
if(BLOCKBREAKER3D_ENABLE_AUDIO)
    set(IRRKLANG_SEARCH_ROOTS)
    if(IRRKLANG_ROOT)
        list(APPEND IRRKLANG_SEARCH_ROOTS ${IRRKLANG_ROOT})
    endif()
    if(DEFINED ENV{IRRKLANG_ROOT} AND NOT "$ENV{IRRKLANG_ROOT}" STREQUAL "")
        list(APPEND IRRKLANG_SEARCH_ROOTS $ENV{IRRKLANG_ROOT})
    endif()
    list(REMOVE_DUPLICATES IRRKLANG_SEARCH_ROOTS)

    set(IRRKLANG_INCLUDE_HINTS ${PROJECT_SOURCE_DIR}/external/vendor/include)
    foreach(root IN LISTS IRRKLANG_SEARCH_ROOTS)
        list(APPEND IRRKLANG_INCLUDE_HINTS ${root}/include)
    endforeach()

    find_path(
        IRRKLANG_INCLUDE_DIR
        NAMES irrKlang.h
        HINTS ${IRRKLANG_INCLUDE_HINTS}
        PATH_SUFFIXES irrKlang
    )

    set(IRRKLANG_LIB_HINTS ${PROJECT_SOURCE_DIR}/external/vendor/lib)
    foreach(root IN LISTS IRRKLANG_SEARCH_ROOTS)
        list(APPEND IRRKLANG_LIB_HINTS
            ${root}/lib
            ${root}/lib/Winx64-visualStudio
            ${root}/lib/Win32-visualStudio
            ${root}/bin/linux-gcc-64
        )
    endforeach()
    list(REMOVE_DUPLICATES IRRKLANG_LIB_HINTS)

    if(WIN32)
        set(IRRKLANG_LIB_NAMES IrrKlang irrKlang)
    else()
        set(IRRKLANG_LIB_NAMES IrrKlang irrklang)
    endif()

    find_library(
        IRRKLANG_LIBRARY
        NAMES ${IRRKLANG_LIB_NAMES}
        HINTS ${IRRKLANG_LIB_HINTS}
    )

    if(NOT IRRKLANG_INCLUDE_DIR OR NOT IRRKLANG_LIBRARY)
        if(WIN32)
            message(FATAL_ERROR "Unable to locate irrKlang. Set IRRKLANG_ROOT to your SDK path or place it under external/vendor.")
        else()
            message(WARNING "irrKlang not found. Audio will be disabled until the SDK is installed.")
            set(BLOCKBREAKER3D_ENABLE_AUDIO OFF)
        endif()
    endif()
endif()
# -------------------------------------------------------------------------------

find_path(
    STB_INCLUDE_DIR
    NAMES stb/stb_image.h
    HINTS
        ${PROJECT_SOURCE_DIR}/external/vendor/include
        /usr/include
        /usr/local/include
)

if(NOT STB_INCLUDE_DIR)
    message(FATAL_ERROR "stb_image.h not found. Install the stb headers via your package manager.")
endif()

set(PROJECT_SOURCES
    src/main.cpp
    src/audio/audio.cpp
    src/core/boilerPlate.cpp
    src/core/shaderClass.cpp
    src/core/Texture.cpp
    src/core/stb.cpp
    src/core/glad.c
    src/core/gl/EBO.cpp
    src/core/gl/VAO.cpp
    src/core/gl/VBO.cpp
    src/game/block.cpp
    src/game/particleSystem.cpp
    src/game/render.cpp
    src/game/vertices.cpp
    src/ui/interface.cpp
)

add_library(
    imgui
    STATIC
        external/imgui/imgui.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_impl_glfw.cpp
        external/imgui/imgui_impl_opengl3.cpp
)

target_include_directories(
    imgui
    PUBLIC
        ${PROJECT_SOURCE_DIR}/external/imgui
        ${PROJECT_SOURCE_DIR}/external/vendor/include
)

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui PUBLIC glfw)

add_executable(BlockBreaker3D ${PROJECT_SOURCES})

target_include_directories(
    BlockBreaker3D
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/BlockBreaker3D
        ${PROJECT_SOURCE_DIR}/external/vendor/include
        ${PROJECT_SOURCE_DIR}/external/imgui
        ${STB_INCLUDE_DIR}
)

target_link_libraries(
    BlockBreaker3D
    PRIVATE
        OpenGL::GL
        glfw
        glm::glm
        Threads::Threads
        imgui
)

if(UNIX AND NOT APPLE)
    target_link_libraries(BlockBreaker3D PRIVATE dl)
endif()

if(MSVC)
    target_compile_options(BlockBreaker3D PRIVATE /W4 /permissive- /EHsc)
else()
    target_compile_options(BlockBreaker3D PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BLOCKBREAKER3D_ENABLE_AUDIO)
    target_include_directories(BlockBreaker3D PRIVATE ${IRRKLANG_INCLUDE_DIR})
    target_link_libraries(BlockBreaker3D PRIVATE ${IRRKLANG_LIBRARY})
    target_compile_definitions(BlockBreaker3D PRIVATE BLOCKBREAKER3D_ENABLE_AUDIO)
endif()

add_custom_command(
    TARGET BlockBreaker3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:BlockBreaker3D>/assets
    COMMENT "Copying asset files"
)

source_group(TREE ${PROJECT_SOURCE_DIR}/src FILES ${PROJECT_SOURCES})

if(BLOCKBREAKER3D_ENABLE_AUDIO)
    message(STATUS "irrKlang include dir: ${IRRKLANG_INCLUDE_DIR}")
    message(STATUS "irrKlang library: ${IRRKLANG_LIBRARY}")
else()
    message(STATUS "irrKlang audio disabled; building with stubbed audio backend.")
endif()

