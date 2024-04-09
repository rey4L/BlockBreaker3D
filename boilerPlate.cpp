#include "boilerPlate.h"

// Function to initialize GLFW
void initializeGLFW() {
    // Initialize GLFW
    glfwInit();
    // Tell GLFW what version of OpenGL we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Function to create a GLFW window
GLFWwindow* createGLFWWindow(int width, int height, const char* title) {
    // Create a GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);
    return window;
}

// Function to initialize GLAD
void initializeGLAD() {
    // Load GLAD so it configures OpenGL
    gladLoadGL();
}

// Function to setup viewport
void setupViewport(int width, int height) {
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, width, height);
}