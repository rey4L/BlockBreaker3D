#include "PowerUps.h"
#include <GLFW/glfw3.h>

Powerups::Powerups() : powerWH(0.12), powerBatX(0.0), powerBallX(0.0), powerLifeX(0.0),
powerBatY(0.0), powerBallY(0.0), powerLifeY(0.0), power_vy(0.0) {
    // Initialize other member variables here if needed
}

void Powerups::drawPowerups() {
    // Draw powerups using GLFW
    // Example: Draw a square for each powerup
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(powerBatX - powerWH / 2, powerBatY - powerWH / 2, 0.0);
    glVertex3f(powerBatX + powerWH / 2, powerBatY - powerWH / 2, 0.0);
    glVertex3f(powerBatX + powerWH / 2, powerBatY + powerWH / 2, 0.0);
    glVertex3f(powerBatX - powerWH / 2, powerBatY + powerWH / 2, 0.0);
    // Add vertices for other powerups similarly
    glEnd();
}

void Powerups::updatePowerups(float deltaTime) {
    // Update powerup positions based on time
    // Example: Move powerups vertically
    powerBatY += power_vy * deltaTime;
    // Add similar updates for other powerups
}


void Powerups::generatePowerups() {
    // Generate new powerups based on game logic
    // Example: Randomly generate powerup positions
}
