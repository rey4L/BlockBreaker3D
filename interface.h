#ifndef INTERFACE_H
#define INTERFACE_H

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

extern bool showMenu;
extern bool isPaused;

void renderMenu();
void renderPauseMenu();

#endif