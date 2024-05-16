#include "block.h"

Cube::Cube(glm::vec3 pos, float scl, const glm::vec3& col) : position(pos), scale(scl), isDestroyed(false), color(col) {}

void Cube::render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize / sizeof(int), GL_UNSIGNED_INT, 0); // Draw the cubes as wireframes (n-1 lines)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Collision detection using the cube's face normals (SAT approach)
//bool Cube::collidesWith(glm::vec3 point, float radius) {
//    if (isDestroyed) {
//        return false;
//    }
//
//    // Calculate the minimum and maximum coordinates of the cube
//    float halfScale = scale * 0.25f;
//    glm::vec3 minPos = position - halfScale;
//    glm::vec3 maxPos = position + halfScale;
//
//    // Check for overlap on each axis
//    float overlap = std::min(maxPos.x - point.x, point.x - minPos.x);
//    if (overlap > radius) return false;
//
//    overlap = std::min(maxPos.y - point.y, point.y - minPos.y);
//    if (overlap > radius) return false;
//
//    overlap = std::min(maxPos.z - point.z, point.z - minPos.z);
//    if (overlap > radius) return false;
//
//    // Check for collision on the cube's face normals
//    glm::vec3 closestPoint = glm::clamp(point, minPos, maxPos);
//    glm::vec3 normal = glm::normalize(point - closestPoint);
//    float distance = glm::length(point - closestPoint);
//
//    if (distance <= radius) {
//        isDestroyed = true;
//        return true;
//    }
//
//    // Debugging code
//    /*std::cout << "cube position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
//    std::cout << "sphere position: (" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
//    std::cout << "distance: " << distance << ", radius: " << radius << std::endl;*/
//
//    return false;
//}

// Collision detection using the cube's face normals (SAT approach)
//bool Cube::collidesWith(glm::vec3 point, float radius) {
//    if (isDestroyed) {
//        return false;
//    }
//
//    // Calculate the minimum and maximum coordinates of the cube
//    float halfScale = scale * 0.35f;
//    glm::vec3 minPos = position - halfScale;
//    glm::vec3 maxPos = position + halfScale;
//
//    // Check for overlap on each axis
//    float overlap = std::min(maxPos.x - point.x, point.x - minPos.x);
//    if (overlap > radius) return false;
//
//    overlap = std::min(maxPos.y - point.y, point.y - minPos.y);
//    if (overlap > radius) return false;
//
//    overlap = std::min(maxPos.z - point.z, point.z - minPos.z);
//    if (overlap > radius) return false;
//
//    // Check for collision on the cube's face normals
//    glm::vec3 closestPoint = glm::clamp(point, minPos, maxPos);
//    glm::vec3 normal = glm::normalize(point - closestPoint);
//    float distance = glm::length(point - closestPoint);
//
//    if (distance <= radius) {
//        // Check if the closest point is on the cube's surface
//        float epsilon = 1e-5f;
//        if (glm::abs(closestPoint.x - minPos.x) < epsilon ||
//            glm::abs(closestPoint.x - maxPos.x) < epsilon ||
//            glm::abs(closestPoint.y - minPos.y) < epsilon ||
//            glm::abs(closestPoint.y - maxPos.y) < epsilon ||
//            glm::abs(closestPoint.z - minPos.z) < epsilon ||
//            glm::abs(closestPoint.z - maxPos.z) < epsilon) {
//            isDestroyed = true;
//            return true;
//        }
//    }
//
//    return false;
//}

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
    float distanceSquared = glm::dot(delta, delta);

    if (distanceSquared > radius * radius) {
        return false;
    }

    // Check for collision on the cube's face normals
    glm::vec3 normal = glm::vec3(0.0f);
    float minOverlap = std::numeric_limits<float>::max();

    for (int i = 0; i < 3; ++i) {
        if (closestPoint[i] == minPos[i]) {
            normal[i] = -1.0f;
            float overlap = point[i] - minPos[i];
            if (overlap < minOverlap) {
                minOverlap = overlap;
            }
        }
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