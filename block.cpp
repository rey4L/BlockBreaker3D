#include "block.h"

Cube::Cube(glm::vec3 pos, float scl) : position(pos), scale(scl) {}

void Cube::render(Shader& shader, int& modelLoc, VAO& vao, const unsigned int* indices, size_t indicesSize) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indicesSize / sizeof(int), GL_UNSIGNED_INT, 0);
}

bool Cube::collidesWith(glm::vec3 point) {
    // Implement collision detection logic here
    return false; // Placeholder
}