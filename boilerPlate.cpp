#include "boilerPlate.h"

void initializeGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createGLFWWindow(int width, int height, const char* title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    return window;
}

void initializeGLAD() {
    gladLoadGL();
}

void setupViewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void colorBufferInit(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    
    // Reset the ball's position and velocity
    tra_x = 0.0f;
    tra_y = 0.35f;
    tra_z = -10.0f;

    ball_velocity_x = 5.0f;
    ball_velocity_y = 5.0f;
    ball_velocity_z = 0.0f;

    // Randomize intiial ball velocity and reset ball default position on reset
    position_y = -2.0f;
    ball_speed = 7.5f;
    randomizeTrajectory(ball_speed);

    cubes.clear();

    // Reset the blocks
    for (auto& cube : cubes) {
        cube.isDestroyed = false;
    }

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

    // Reset multi hit counter (white blocks counter)
    multiHitCount = 0;
   
    // Ensure the game is not paused or marked as over
    isPaused = false;
    isGameOver = false;
    showPowerUp = false;
}