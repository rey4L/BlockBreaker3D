#include "interface.h"

// Game state constants
const int GAME_STATE_MENU = 0;
const int GAME_STATE_GAMEPLAY = 1;
const int GAME_STATE_PAUSE = 2;

bool showMenu = true;
bool isPaused = false;

void renderMenu() {
    ImGui::Begin("Menu");
    if (ImGui::Button("Start")) {
        showMenu = false;
    }
    ImGui::End();
}

void renderPauseMenu() {
    ImGui::Begin("Pause Menu");
    if (ImGui::Button("Resume")) {
        isPaused = false;
    }
    ImGui::End();
}