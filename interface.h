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

extern float backgroundMusicVolume;
extern float soundEffectsVolume;

void renderMenu();
void renderPauseMenu();
void renderGameOverMenu();

#endif