#include "particleSystem.h"

ParticleSystem::ParticleSystem(const char* vertexPath, const char* fragmentPath)
    : shader(vertexPath, fragmentPath) {
    // Initialize VBO and VAO for particles
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * 10000, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, lifespan));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, size));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
}

void ParticleSystem::setColor(glm::vec4 color) {
    int colorLoc = glGetUniformLocation(shader.ID, "particleColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(color));
}

void ParticleSystem::addParticle(glm::vec3 position, glm::vec3 velocity, float lifespan, float size) {
    Particle particle = { position, velocity, lifespan, size, 1.0f };
    particles.push_back(particle);
}

void ParticleSystem::update(float deltaTime) {
    for (auto it = particles.begin(); it != particles.end();) {
        it->position += it->velocity * deltaTime;
        it->lifespan -= deltaTime;
        it->fade -= deltaTime / it->lifespan;
        if (it->lifespan <= 0.0f || it->fade <= 0.1f) {
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void ParticleSystem::draw(glm::mat4 view, glm::mat4 projection) {
    shader.Activate();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * particles.size(), particles.data());

    int viewLoc = glGetUniformLocation(shader.ID, "view");
    int projLoc = glGetUniformLocation(shader.ID, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    glDrawArrays(GL_POINTS, 0, particles.size());

    glBindVertexArray(0);
    shader.Delete();
}