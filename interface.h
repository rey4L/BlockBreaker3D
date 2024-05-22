#ifndef INTERFACE_H
#define INTERFACE_H

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include <stdlib.h>

extern bool showMenu;
extern bool isPaused;
extern bool isGameOver;
extern bool resetGame;
extern bool showHelp;
extern int score;
extern bool showPowerUp;

extern float messageTimer;
extern const float MESSAGE_DURATION;

extern float backgroundMusicVolume;
extern float soundEffectsVolume;

void imguiInit(GLFWwindow* window);
void imguiNewFrame();
void renderMenu();
void renderHelpWindow();
void renderPauseMenu();
void updateScore();
void showPowerUpMessage(float deltaTime);
void renderGameOverMenu();
void imguiCleanup();

#endif