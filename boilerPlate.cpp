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

int multiHitCount = 0;

void resetGameState(Audio& audio) {
    // Reset the pause menu flag
    isPaused = false;

    // Reset bgm
    if (!audio.isBackgroundMusicPlaying) {
        audio.playBackgroundMusic();
        audio.setBackgroundMusicVolume(backgroundMusicVolume);
    }

    //audio.playBackgroundMusic();
    
    // Reset the ball's position and velocity
    tra_x = 0.0f;
    tra_y = 0.35f;
    tra_z = -10.0f;

    ball_velocity_x = 5.0f;
    ball_velocity_y = 5.0f;
    ball_velocity_z = 0.0f;

    position_y = -2.0f;

    // Reset the blocks
    for (auto& cube : cubes) {
        cube.isDestroyed = false;
    }

    // Reset the transition flag
    isTransitioning = false;

    // Reset cube states (not destroyed)
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 7; ++col) {
            float normalizedX = gameWorldMinX + col * blockSpacingX + blockSpacingX / 2.0f;
            float normalizedY = gameWorldMinY + row * blockSpacingY + blockSpacingY / 2.0f;
            Cube cube(glm::vec3(normalizedX, normalizedY, gameWorldZ), blockSize, cubeColors[currentColorIndex]);
            currentColorIndex = (currentColorIndex + 1) % (sizeof(cubeColors) / sizeof(cubeColors[0]));
            cubes.push_back(cube);
        }
    }

    // Reset multi hit counter
    multiHitCount = 0;
   
    // Ensure the game is not paused or marked as over
    isPaused = false;
    isGameOver = false;
}

// Function to apply a power-up to a random block
void applyPowerUp(std::vector<Cube>& cubes) {
    if (multiHitCount >= 5) {
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cubes.size() - 1);

    int randomIndex = dis(gen);

    if (!cubes[randomIndex].isDestroyed) {
        // Apply power-up logic here
        cubes[randomIndex].color = glm::vec3(1.0f, 1.0f, 1.0f); // White
        multiHitCount++;
    }
}

bool areAllBlocksDestroyed(const std::vector<Cube>& cubes) {
    for (const auto& cube : cubes) {
        if (!cube.isDestroyed) {
            return false;
        }
    }
    return true;
}