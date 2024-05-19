#ifndef POWERUPS_H
#define POWERUPS_H


#include "Texture.h"
class Powerups {
public:
    Powerups();
    void drawPowerups();
    void updatePowerups(float deltaTime);

private:
    void generatePowerups();
    // Add other member variables and functions as needed

    float powerWH;
    float powerBatX, powerBallX, powerLifeX;
    float powerBatY, powerBallY, powerLifeY;
    float power_vy;
};

#endif
