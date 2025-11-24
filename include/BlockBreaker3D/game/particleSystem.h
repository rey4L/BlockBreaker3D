#ifndef PARTICLESYSTEM_CLASS_H
#define PARTICLESYSTEM_CLASS_H

#include <glad/glad.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/glm.hpp>
#include <vector>
#include "core/shaderClass.h"

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float lifespan;
    float size;
    float fade;
};

class ParticleSystem {
public:
    std::vector<Particle> particles;
    unsigned int VAO, VBO;
    Shader shader;

    ParticleSystem(const char* vertexPath, const char* fragmentPath);
    void setColor(glm::vec4 color);
    void addParticle(glm::vec3 position, glm::vec3 velocity, float lifespan, float size);
    void update(float deltaTime);
    void draw(glm::mat4 view, glm::mat4 projection);
};

#endif