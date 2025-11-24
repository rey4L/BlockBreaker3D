# BlockBreaker3D

BlockBreaker3D revives the classic block breaker experience in a 3D arena with OpenGL rendering, irrKlang audio, and an ImGui-powered HUD.

## Features

- **Immersive 3D gameplay** – paddle, ball, particles, and lighting are rendered with GL 3.3.
- **Responsive UI** – Dear ImGui overlays handle menus, score, countdowns, and power-up prompts.
- **Layered audio** – irrKlang manages looping music, power-up cues, and collision effects.

## Project Layout

```
BlockBreaker3D/
├── assets/
│   ├── audio/            # wav assets
│   ├── fonts/            # ImGui font(s)
│   ├── shaders/          # GLSL sources
│   └── textures/         # window icons & misc
├── legacy/
│   └── msvc/             # Archived Visual Studio solution files & samples
├── cmake/
│   └── toolchains/
│       └── mingw-w64.cmake
├── external/
│   ├── imgui/            # Dear ImGui sources
│   └── vendor/           # bundled headers/libs (glad, irrKlang, etc.)
│       └── bin/          # prebuilt runtime DLLs (Windows)
├── include/
│   └── BlockBreaker3D/
│       ├── audio/
│       ├── core/
│       │   └── gl/
│       ├── game/
│       └── ui/
├── src/
│   ├── audio/
│   ├── core/
│   │   └── gl/
│   ├── game/
│   └── ui/
├── CMakeLists.txt
└── README.md
```

## Dependencies

| Component      | Purpose                        | Arch Linux package / source                 |
|----------------|--------------------------------|---------------------------------------------|
| CMake ≥ 3.20   | Build configuration            | `sudo pacman -S cmake`                      |
| GCC/Clang      | C++20 compiler                 | `sudo pacman -S base-devel`                 |
| OpenGL + GLFW  | Rendering & windowing          | `sudo pacman -S glfw-x11` (or `glfw-wayland`) |
| GLM            | Math utilities                 | `sudo pacman -S glm`                        |
| stb            | Texture loading                | `sudo pacman -S stb`                        |
| irrKlang 1.6+ (optional) | Audio playback (full feature set) | Download from [ambiera.com/irrklang](https://www.ambiera.com/irrklang/downloads.html) |

> ℹ️ irrKlang is not on the official Arch repos. Download the SDK, extract it somewhere (e.g. `~/SDKs/irrklang`), and point the `IRRKLANG_ROOT` CMake cache entry at that directory. The repo keeps the original Windows `.lib` files under `external/vendor/lib`; Linux users still need the official `libIrrKlang.so`.  
>  
> 🚫 No irrKlang? The game still builds/run with a stubbed audio backend (no sound effects) on platforms where the SDK isn’t installed.

## Build & Run (Linux)

```bash
# configure (Debug, for example)
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Debug \
  -DIRRKLANG_ROOT=/path/to/irrklang-sdk

# compile
cmake --build build --config Debug

# run from the binary dir (assets are copied automatically)
./build/bin/BlockBreaker3D
```

- Use `-DCMAKE_BUILD_TYPE=Release` for optimized builds.
- If irrKlang lives somewhere unusual, keep passing `-DIRRKLANG_ROOT=/abs/path`.
- The build copies `assets/` next to the executable so relative resource paths still work.

## Build (Windows)

### Visual Studio (MSVC)
```powershell
cmake -S . -B build ^
  -G "Visual Studio 17 2022" -A x64 ^
  -DIRRKLANG_ROOT=C:/SDKs/irrklang-1.6.0

cmake --build build --config Release
```

Open `build/BlockBreaker3D.sln` if you prefer the IDE. Assets land in `build/bin/Release/assets`, so running from the Visual Studio debugger works without extra tweaks.

### MinGW-w64
```bash
cmake -S . -B build-mingw -G "MinGW Makefiles" -DIRRKLANG_ROOT=Z:/SDKs/irrklang
cmake --build build-mingw --config Release
```

## Audio backend

- **Stub mode (default on Linux):** If the irrKlang SDK isn’t available, CMake automatically builds a silent stub backend so the game still compiles and runs (no music/SFX).
- **Full audio:** Provide the SDK path and reconfigure with  
  `-DBLOCKBREAKER3D_ENABLE_AUDIO=ON -DIRRKLANG_ROOT=/absolute/path/to/irrklang`  
  You’ll need `libIrrKlang.so` (Linux) or the `.lib/.dll` pair (Windows) accessible in that directory.

## Cross-Compile Windows binaries from Linux (optional)

1. Install the MinGW toolchain: `sudo pacman -S mingw-w64-gcc`.
2. Configure with the provided toolchain file:
   ```bash
   cmake -S . -B build-win \
     -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64.cmake \
     -DIRRKLANG_ROOT=$PWD/external/vendor
   cmake --build build-win --config Release
   ```
3. The resulting `.exe` and copied assets live under `build-win/bin`.

Make sure `IRRKLANG_ROOT` points at a directory containing `lib/IrrKlang.lib` (the repo’s `external/vendor/lib/Winx64-visualStudio` works for quick tests).

## Notes

- Legacy `.vcxproj` files remain for reference but are no longer maintained—the CMake build is now the source of truth.
- Assets are referenced via relative paths (e.g., `assets/audio/bgm.wav`), so run the game from the build output directory or copy the assets folder next to the executable if you deploy elsewhere.

## Attributions

- Thanks to Victor Gordon for the excellent [OpenGL tutorials](https://github.com/VictorGordan/opengl-tutorials).
- Sound effects originate from [Pixabay](https://pixabay.com/sound-effects/).
