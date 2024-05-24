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

void updatePaddlePosition(PaddleState* paddleState, double deltaTime, ParticleSystem& particleSystem) {
    if (paddleState == nullptr) return;

    float speed = 7.5f; // Speed of paddle movement
    float edgeLimit = 2.0f; // How far the paddle can go to the left or right
    const float leftEdge = -edgeLimit;
    const float rightEdge = edgeLimit;

    // Store the previous position
    static glm::vec3 lastPaddlePos = glm::vec3(paddleState->x_pos, paddleState->y_pos, paddleState->z_pos);

    // Update the paddle's position based on its direction and the speed
    paddleState->x_pos += paddleState->direction * speed * deltaTime;

    // Ensure the paddle doesn't move beyond the edges of the play area
    paddleState->x_pos = std::max(leftEdge, std::min(paddleState->x_pos, rightEdge));

    // Calculate current paddle position
    glm::vec3 currentPaddlePos = glm::vec3(paddleState->x_pos, paddleState->y_pos, paddleState->z_pos);

    glm::vec3 leftOffset = glm::vec3(-1.09f, 0.0f, 0.0f);
    glm::vec3 rightOffset = glm::vec3(1.29f, 0.0f, 0.0f);

    // REnder tracers when paddle is moved
    if (glm::length(currentPaddlePos - lastPaddlePos) > 0.0f) {
        glm::vec3 velocity = glm::vec3(-2.0f, 0.0f, 0.0f);
        float particleSize = 45.0f;
        float particleLifespan = 0.1115f;

        glPointSize(particleSize);
        particleSystem.addParticle(currentPaddlePos + leftOffset, velocity, particleLifespan, particleSize); // Left side
        particleSystem.addParticle(currentPaddlePos + rightOffset, velocity, particleLifespan, particleSize); // Right side
    }

    // Update the last position
    lastPaddlePos = currentPaddlePos;
}

void updateBallPosition(float& tra_x, float& position_y, float& tra_z,
    float& ball_velocity_x, float& ball_velocity_y, float& ball_velocity_z,
    float deltaTime, Audio& audio, bool& isGameOver) {
    
    // Update ball position
    tra_x += ball_velocity_x * deltaTime;
    position_y += ball_velocity_y * deltaTime;
    tra_z += ball_velocity_z * deltaTime;

    // Scene boundaries
    float left_boundary = -2.5f;
    float right_boundary = 2.5f;
    float top_boundary = 2.5f;
    float bottom_boundary = -3.5f;
    float front_boundary = -15.0f;
    float back_boundary = -5.0f;

    const float collisionBuffer = 0.1f; // Prevent edge cases of ball position matching boundary exactly

    if (tra_x <= left_boundary + collisionBuffer) {
        tra_x = left_boundary + collisionBuffer;  
        ball_velocity_x = -ball_velocity_x;
        audio.playResponseSound();
    }

    if (tra_x >= right_boundary - collisionBuffer) {
        tra_x = right_boundary - collisionBuffer;  
        ball_velocity_x = -ball_velocity_x;
        audio.playResponseSound();
    }

    if (position_y <= bottom_boundary + collisionBuffer) {
        audio.stopBackgroundMusic();
        audio.playGameOverSound();
        isGameOver = true;
    }

    if (position_y >= top_boundary - collisionBuffer) {
        position_y = top_boundary - collisionBuffer;  
        ball_velocity_y = -ball_velocity_y;
        audio.playResponseSound();
    }

    if (tra_z <= front_boundary + collisionBuffer) {
        tra_z = front_boundary + collisionBuffer;  
        ball_velocity_z = -ball_velocity_z;
    }
    if (tra_z >= back_boundary - collisionBuffer) {
        tra_z = back_boundary - collisionBuffer;  
        ball_velocity_z = -ball_velocity_z;
    }
}

void handlePaddleCollision(glm::vec3& spherePosition, glm::vec3& velocity, glm::vec3& paddlePos,
    float sphereRadius, float& ball_velocity_x, float& ball_velocity_y,
    float& ball_velocity_z, Audio& audio, float paddleWidth, float paddleHeight, 
    float paddleDepth) {

    // Collision detection with the paddle
    if (spherePosition.x >= paddlePos.x - paddleWidth &&
        spherePosition.x <= paddlePos.x + paddleWidth &&
        spherePosition.y >= paddlePos.y - paddleHeight &&
        spherePosition.y <= paddlePos.y + paddleHeight &&
        spherePosition.z >= paddlePos.z - paddleDepth &&
        spherePosition.z <= paddlePos.z + paddleDepth) {

        // Calculate collision normal based on the ball's position relative to the paddle's center
        glm::vec3 relativePosition = spherePosition - paddlePos;
        glm::vec3 collisionNormal = glm::vec3(0, 1, 0); // Default normal for top surface collision (horizontal)

        audio.playResponseSound();

        // If the ball is rolling along the paddle, force a bounce
        if (std::abs(relativePosition.y) < sphereRadius) {
            collisionNormal = glm::vec3(0, 1, 0); // Force the ball to bounce upwards
        }

        else {
            collisionNormal = glm::normalize(relativePosition); // Reflect based on the relative position
        }

        glm::vec3 reflectedVelocity = glm::reflect(velocity, collisionNormal);

        // Ensure the ball bounces up
        reflectedVelocity.y = std::abs(reflectedVelocity.y); // Force the y-component to be positive

        ball_velocity_x = reflectedVelocity.x;
        ball_velocity_y = reflectedVelocity.y;
        ball_velocity_z = reflectedVelocity.z;
    }
}

void randomizeTrajectory(float speed) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> distr_x(-1.0, 1.0);
    static std::uniform_real_distribution<> distr_y(0.1, 1.0);

    // Randomize ball's initial velocities
    glm::vec2 initialVelocity;

    // Ensure the initial velocity is non-zero and has a reasonable magnitude
    do {
        initialVelocity.x = distr_x(gen);
        initialVelocity.y = distr_y(gen);
    } while (glm::length(initialVelocity) < 0.1f);  // Avoid very small magnitudes

    // Normalize the vector to make it a unit vector and then scale by speed
    initialVelocity = glm::normalize(initialVelocity) * speed;

    // Set the ball's velocity
    ball_velocity_x = initialVelocity.x;
    ball_velocity_y = initialVelocity.y;
}

void resetPaddleSize() {
    radius = 0.70f / 2;
    length = 2.25f;
    updatePaddleVertices(pill_vertices, pill_indices, radius, length);
}

void incrementScore(int points) {
    score += points;
}