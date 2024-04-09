#include "render.h"

// Close window upon ESC keypress
//void key(GLFWwindow* window, int k, int s, int action, int mods)
//{
//    if (action == GLFW_PRESS || action == GLFW_REPEAT) return;
//
//    PaddleState* paddleState = reinterpret_cast<PaddleState*>(glfwGetWindowUserPointer(window)); // Get paddle state from GLFW window glfwGetWindowUserPointer(window);
//
//    switch (k) {
//    case GLFW_KEY_ESCAPE:
//        glfwSetWindowShouldClose(window, GLFW_TRUE);
//        break;
//    case GLFW_KEY_A:
//        paddleState->x_pos -= 0.1f; // Move left
//        break;
//    case GLFW_KEY_D:
//        paddleState->x_pos += 0.1f; // Move right
//        break;
//    default:
//        return;
//    }
//}

void key(GLFWwindow* window, int k, int s, int action, int mods)
{
    PaddleState* paddleState = reinterpret_cast<PaddleState*>(glfwGetWindowUserPointer(window)); // Get paddle state from GLFW window glfwGetWindowUserPointer(window);
    if (!paddleState) return;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (k) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_A:
            paddleState->direction -= 1.0f; // Move left
            break;
        case GLFW_KEY_D:
            paddleState->direction += 1.0f; // Move right
            break;
        default:
            return;
        }
    }
    else if (action == GLFW_RELEASE) {
        if (k == GLFW_KEY_A || k == GLFW_KEY_D) {
            paddleState->direction = 0.0f;
        }
    }
}


// Function to update rotation
void updateRotation(float& rotation, double& prevTime, const double currentTime, const float rotationSpeed, const double timeInterval) {

    if (currentTime - prevTime >= timeInterval) {
        rotation += rotationSpeed;
        prevTime = currentTime;
    }
}

// Bounce pls
void bounce(const double currentTime, double previousTime, float& gravity, float& position, float& velocity, float& damping, float& groundLevel, float& minimumVelocity, int& bounceCount, const int maxBounces) {

    double deltaTime = currentTime - previousTime; // Calculate delta time
    previousTime = currentTime;

    position += velocity * deltaTime;
    velocity += gravity * deltaTime;

    // Check for bounce
    if (position <= groundLevel) {
        position = groundLevel;
        if (abs(velocity) < minimumVelocity || bounceCount >= maxBounces)
        {
            velocity = 5.5f;
            position = groundLevel;
        }
        else
        {
            velocity = velocity * -damping;
            bounceCount++;
        }
    }
}