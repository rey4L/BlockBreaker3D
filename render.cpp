#include "render.h"

void key(GLFWwindow* window, int k, int s, int action, int mods)
{
    PaddleState* paddleState = reinterpret_cast<PaddleState*>(glfwGetWindowUserPointer(window)); // Get paddle state from GLFW window glfwGetWindowUserPointer(window);
    if (!paddleState) return;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (k) {
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

void updatePaddlePosition(PaddleState* paddleState, double deltaTime) {
    if (paddleState == nullptr) return;

    float speed = 7.5f; // Speed of paddle movement
    float edgeLimit = 2.0f; // How far the paddle can go to the left or right
    const float leftEdge = -edgeLimit;
    const float rightEdge = edgeLimit;

    // Update the paddle's position based on its direction and the speed
    paddleState->x_pos += paddleState->direction * speed * deltaTime;

    // Ensure the paddle doesn't move beyond the edges of the play area
    paddleState->x_pos = std::max(leftEdge, std::min(paddleState->x_pos, rightEdge));
}
