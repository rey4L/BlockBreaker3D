#include "interface.h"

bool showMenu = true;
bool isPaused = false;

void renderMenu() {
    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(300, 250));
    ImGui::SetWindowPos(ImVec2(250, 250));

    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("Welcome to Brick Breaker 3D!").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text("\n\nWELCOME TO BLOCK BREAKER 3D!");

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.35f);

    ImVec2 buttonSize(120, 30);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("PLAY", buttonSize)) {
        showMenu = false;
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Start Game").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.5f);

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("OPTIONS", buttonSize)) {
        // Add code to handle options menu
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Options").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.65f);

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("QUIT", buttonSize)) {
        // Add code to handle options menu
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Quit").x) * 0.5f);

    ImGui::PopStyleVar();

    ImGui::End();
}

void renderPauseMenu() {
    ImGui::Begin("Pause Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(200, 200));
    ImGui::SetWindowPos(ImVec2(250, 250));

    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("Game Paused").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text("\n\nGAME PAUSED");

    // Set button size
    ImVec2 buttonSize(90, 20);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.45f); // Adjust the factor (0.4f) as needed

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("RESUME", buttonSize)) {
        isPaused = false;
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Resume").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.6f); // Adjust the factor (0.6f) as needed

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("RESTART", buttonSize)) {
        // Add code to restart the game
    }
    ImGui::SetCursorPosX(windowWidth - ImGui::CalcTextSize("Restart").x * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.75f); // Adjust the factor (0.8f) as needed

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("MAIN MENU", buttonSize)) {
        isPaused = false;
        showMenu = true;
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Main Menu").x) * 0.5f);

    ImGui::PopStyleVar();
    ImGui::End();
}