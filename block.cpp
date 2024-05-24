#include "block.h"

Cube::Cube(glm::vec3 pos, float scl, const glm::vec3& col) : position(pos), scale(scl), isDestroyed(false), color(col) {}

void Cube::render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize / sizeof(int), GL_UNSIGNED_INT, 0); // Draw the cubes as wireframes (n-1 lines)
}

bool Cube::collidesWith(glm::vec3 point, float radius) {
    if (isDestroyed) {
        return false;
    }

    // Calculate the minimum and maximum coordinates of the cube
    float halfScale = scale * 0.5f;
    glm::vec3 minPos = position - halfScale;
    glm::vec3 maxPos = position + halfScale;

    // Check for overlap on each axis
    glm::vec3 closestPoint = glm::clamp(point, minPos, maxPos);
    glm::vec3 delta = point - closestPoint;
    float distanceSquared = glm::dot(delta, delta); // Using dot product for efficiency

    if (distanceSquared > radius * radius) {
        return false;
    }

    // Check for collision on the cube's face normals
    glm::vec3 normal = glm::vec3(0.0f);
    float minOverlap = std::numeric_limits<float>::max();

    // Check if the closest point is on the minimum side of the cube
    for (int i = 0; i < 3; ++i) {
        if (closestPoint[i] == minPos[i]) {
            normal[i] = -1.0f; // Set the normal direction
            float overlap = point[i] - minPos[i];
            if (overlap < minOverlap) {
                minOverlap = overlap; // Update minimum overlap
            }
        }
        // Check if the closest point is on the maximum side of the cube
        else if (closestPoint[i] == maxPos[i]) {
            normal[i] = 1.0f;
            float overlap = maxPos[i] - point[i];
            if (overlap < minOverlap) {
                minOverlap = overlap;
            }
        }
    }

    if (minOverlap <= radius) {
        isDestroyed = true;
        return true;
    }

    return false;
}

// Function that designates random blocks the potential to activate a power up
void applyPowerUp(std::vector<Cube>& cubes, float& paddleWidth, float& length, Audio& audio) {
    if (multiHitCount >= 5) {
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cubes.size() - 1);

    int randomIndex = dis(gen);

    if (!cubes[randomIndex].isDestroyed) {
        cubes[randomIndex].color = glm::vec3(1.0f, 1.0f, 1.0f);
        multiHitCount++;

        // 2% chance of getting a power-up from the randomly selected white blocks
        std::uniform_real_distribution<>powerUpDis(0.0f, 1.0f);
        float powerUpChance = powerUpDis(gen);
        
        if (powerUpChance <= 0.02f) 
        {
            std::uniform_int_distribution<> powerUpTypeDis(0, 1);
            int powerUpType = powerUpTypeDis(gen);

            if (powerUpType == 0) {
                
                // Increase paddle size and ball speed by 4.5%
                float scaleFactor = 1.045f;
                paddleWidth *= scaleFactor;
                length *= scaleFactor;

                ball_speed *= scaleFactor;

                audio.playPowerUpSound();
                updatePaddleVertices(pill_vertices, pill_indices, radius, length);

                // Reset power-up notification flag and timer
                showPowerUp = true;
                messageTimer = 0.0f;
            }
        }
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