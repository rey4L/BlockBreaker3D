#ifndef POWERUP_H
#define POWERUP_H

#include "vec3.h"
#include <vector>

enum class PowerUpType {
    INCREASE_SPEED,
    DECREASE_SPEED,
    INCREASE_PADDLE_SIZE,
    DECREASE_PADDLE_SIZE,
    EXTRA_LIFE
};
// Forward declaration of GameState class
class GameState;

class PowerUp {
public:
    PowerUp(PowerUpType type, const vec3& position, float radius);

    void applyPowerUp(GameState& gameState);
    void render(); // Add rendering logic if needed

    PowerUpType getType() const;
    vec3 getPosition() const;
    float getRadius() const;
    bool isActive() const;
    void deactivate();

private:
    PowerUpType type;
    vec3 position;
    float radius;
    bool active;
};

void generatePowerUps(std::vector<PowerUp>& powerUps);
bool checkPowerUpCollision(const vec3& spherePosition, float sphereRadius, PowerUp& powerUp);


class GameState {
public:
    float paddleWidth = 0.60f;
    // Other game state variables...
};

#endif // POWERUP_H
