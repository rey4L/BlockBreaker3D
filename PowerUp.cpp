#include "PowerUp.h"
#include "interface.h"
#include "boilerPlate.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
//#include "Texture.h" Effectively removed texture logic but still keeping it in case i need it later - Rey
#include "vertices.h"
#include "block.h"
#include "render.h"
#include <iostream>
#include "audio.h"
#include "PowerUp.h"
#include "vec3.h"
#include <vector>



// Define maximum and minimum speeds
const float MAX_SPEED = 7.0f;
const float MIN_SPEED = 2.0f;

PowerUp::PowerUp(PowerUpType type, const vec3& position, float radius)
    : type(type), position(position), radius(radius), active(true) {}

void PowerUp::applyPowerUp(GameState& gameState) {
    // Define the logic for each power-up type
    switch (type) {
    case PowerUpType::INCREASE_SPEED:
        // Increase ball speed
        ball_velocity_x *= 1.1f; // Increase ball velocity by 10%
        ball_velocity_y *= 1.1f; // Increase ball velocity by 10%


        // Ensure ball speed does not exceed the maximum speed
        if (ball_velocity_x > MAX_SPEED) ball_velocity_x = MAX_SPEED;
        if (ball_velocity_y > MAX_SPEED) ball_velocity_y = MAX_SPEED;


        std::cout << "Increased ball speed!" << std::endl;
        break;
    case PowerUpType::DECREASE_SPEED:
        // Decrease ball speed
        ball_velocity_x *= 0.99f; // Decrease ball velocity by 10%
        ball_velocity_y *= 0.99f; // Decrease ball velocity by 10%

        //// Ensure the ball's velocity does not fall below the minimum threshold
        //    if (std::abs(ball_velocity_x) < MIN_VELOCITY) {
        //        ball_velocity_x = (ball_velocity_x < 0) ? -MIN_VELOCITY : MIN_VELOCITY;
        //    }
        //if (std::abs(ball_velocity_y) < MIN_VELOCITY) {
        //    ball_velocity_y = (ball_velocity_y < 0) ? -MIN_VELOCITY : MIN_VELOCITY;
        //}
           
    // Ensure ball speed does not fall below the minimum speed
    if (ball_velocity_x < MIN_SPEED) ball_velocity_x = MIN_SPEED;
    if (ball_velocity_y < MIN_SPEED) ball_velocity_y = MIN_SPEED;
        std::cout << "Decreased ball speed!" << std::endl;
        break;

    case PowerUpType::INCREASE_PADDLE_SIZE:
        // Increase paddle size
        gameState.paddleWidth *= 1.1f; // Increase paddle width by 10%
        std::cout << "Increased paddle size!" << std::endl;
        break;
    case PowerUpType::DECREASE_PADDLE_SIZE:
        // Decrease paddle size
        gameState.paddleWidth *= 0.9f; // Decrease paddle width by 10%
        std::cout << "Decreased paddle size!" << std::endl;
        break;

    case PowerUpType::EXTRA_LIFE:
        // Add extra life
     //   lives++; // Increment the number of lives
        std::cout << "Extra life!" << std::endl;
        break;
    default:
        break;
    }
}


void PowerUp::render() {
    // Render the power-up on the screen if necessary
}

PowerUpType PowerUp::getType() const {
    return type;
}

vec3 PowerUp::getPosition() const {
    return position;
}

float PowerUp::getRadius() const {
    return radius;
}

bool PowerUp::isActive() const {
    return active;
}

void PowerUp::deactivate() {
    active = false;
}

void generatePowerUps(std::vector<PowerUp>& powerUps) {
    // Generate some power-ups for testing
    powerUps.emplace_back(PowerUpType::INCREASE_SPEED, vec3(0.0f, 0.0f, -10.0f), 0.25f);
    powerUps.emplace_back(PowerUpType::DECREASE_SPEED, vec3(1.0f, 1.0f, -10.0f), 0.25f);
}

bool checkPowerUpCollision(const vec3& spherePosition, float sphereRadius, PowerUp& powerUp) {
    float distance = ::distance(spherePosition, powerUp.getPosition());
    return distance < (sphereRadius + powerUp.getRadius());
}
