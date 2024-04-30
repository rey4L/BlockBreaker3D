#include "block.h"

Cube::Cube(glm::vec3 pos, float scl, const glm::vec3& col) : position(pos), scale(scl), isDestroyed(false), color(col) {}

void Cube::render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize / sizeof(int), GL_UNSIGNED_INT, 0);
}

//bool Cube::collidesWith(glm::vec3 point, float radius) {
//    if (isDestroyed) {
//		return false;
//    }
//
//    // Calculate the minimum and maximum coordinates of the cube
//    float minX = position.x - scale / 1.5f;
//    float maxX = position.x + scale / 1.5f;
//    float minY = position.y - scale / 1.5f;
//    float maxY = position.y + scale / 1.5f;
//    float minZ = position.z - scale / 1.5f;
//    float maxZ = position.z + scale / 1.5f;
//
//    // Check if the sphere intersects with the cube
//    /*float closestX = std::max(minX, std::min(point.x, maxX));
//    float closestY = std::max(minY, std::min(point.y, maxY));
//    float closestZ = std::max(minZ, std::min(point.z, maxZ));
//
//    float distance = std::sqrt(
//        std::pow(closestX - point.x, 2) +
//        std::pow(closestY - point.y, 2) +
//        std::pow(closestZ - point.z, 2)
//    );*/
//
//    // Check for overlap on each axis
//    if (point.x + radius < minX || point.x - radius > maxX) return false;
//    if (point.y + radius < minY || point.y - radius > maxY) return false;
//    if (point.z + radius < minZ || point.z - radius > maxZ) return false;
//
//    // Check for collision on the cube's face normals
//    glm::vec3 closestPoint = glm::clamp(point, glm::vec3(minX, minY, minZ), glm::vec3(maxX, maxY, maxZ));
//    glm::vec3 normal = glm::normalize(point - closestPoint);
//    float distance = glm::length(point - closestPoint);
//
//    // Debugging code
//    /*std::cout << "cube position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
//    std::cout << "sphere position: (" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
//    std::cout << "distance: " << distance << ", radius: " << radius << std::endl;*/
//
//    if (distance < radius) {
//        isDestroyed = true;
//        return true;
//    }
//
//    return false;
//    //return distance < radius;
//}

// Collision detection using the cube's face normals (SAT approach)
bool Cube::collidesWith(glm::vec3 point, float radius) {
    if (isDestroyed) {
        return false;
    }

    // Calculate the minimum and maximum coordinates of the cube
    float halfScale = scale * 0.5f;
    glm::vec3 minPos = position - halfScale;
    glm::vec3 maxPos = position + halfScale;

    // Check for overlap on each axis
    float overlap = std::min(maxPos.x - point.x, point.x - minPos.x);
    if (overlap > radius) return false;

    overlap = std::min(maxPos.y - point.y, point.y - minPos.y);
    if (overlap > radius) return false;

    overlap = std::min(maxPos.z - point.z, point.z - minPos.z);
    if (overlap > radius) return false;

    // Check for collision on the cube's face normals
    glm::vec3 closestPoint = glm::clamp(point, minPos, maxPos);
    glm::vec3 normal = glm::normalize(point - closestPoint);
    float distance = glm::length(point - closestPoint);

    if (distance < radius) {
        isDestroyed = true;
        return true;
    }

    return false;
}