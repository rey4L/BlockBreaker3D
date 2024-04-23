#include "block.h"

Cube::Cube(glm::vec3 pos, float scl) : position(pos), scale(scl), isDestroyed(false) {}

void Cube::render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize / sizeof(int), GL_UNSIGNED_INT, 0);
}

bool Cube::collidesWith(glm::vec3 point, float radius) {
    if (isDestroyed) {
		return false;
    }

    // Calculate the minimum and maximum coordinates of the cube
    float minX = position.x - scale / 2.0f;
    float maxX = position.x + scale / 2.0f;
    float minY = position.y - scale / 2.0f;
    float maxY = position.y + scale / 2.0f;
    float minZ = position.z - scale / 2.0f;
    float maxZ = position.z + scale / 2.0f;

    // Check if the sphere intersects with the cube
    float closestX = std::max(minX, std::min(point.x, maxX));
    float closestY = std::max(minY, std::min(point.y, maxY));
    float closestZ = std::max(minZ, std::min(point.z, maxZ));

    float distance = std::sqrt(
        std::pow(closestX - point.x, 2) +
        std::pow(closestY - point.y, 2) +
        std::pow(closestZ - point.z, 2)
    );

    // Debugging code
    /*std::cout << "cube position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
    std::cout << "sphere position: (" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
    std::cout << "distance: " << distance << ", radius: " << radius << std::endl;*/

    if (distance < radius) {
        isDestroyed = true;
        return true;
    }

    return false;
    //return distance < radius;
}