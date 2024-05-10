#include "interface.h"

bool showMenu = true;
bool isPaused = false;
bool isGameOver = false; 
bool resetGame = false;
bool showHelp = false;

float backgroundMusicVolume = 0.75f;
float soundEffectsVolume = 0.50f;

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
    if (ImGui::Button("SOUND", buttonSize)) {
        ImGui::OpenPopup("Sound Settings");
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Sound").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.65f);

    // Sound settings window
    if (ImGui::BeginPopupModal("Sound Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        // Set the desired width of the popup window
        float popupWidth = 215.0f;
        ImGui::SetNextWindowSize(ImVec2(popupWidth, 0.0f));

        // Add spacing between the title and the first slider
        ImGui::Spacing();

        // Background Music Volume Slider
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.5f); 
        ImGui::Text("Background Music Volume");
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.5f); 
        ImGui::PushItemWidth(200.0f);
        ImGui::SliderFloat("##bgVolume", &backgroundMusicVolume, 0.0f, 1.0f);
        ImGui::PopItemWidth();

        // Add spacing between the sliders
        ImGui::Spacing();

        // Sound Effects Volume Slider
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.5f); 
        ImGui::Text("Sound Effects Volume");
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.5f); 
        ImGui::PushItemWidth(200.0f);
        ImGui::SliderFloat("##sfxVolume", &soundEffectsVolume, 0.0f, 1.0f);
        ImGui::PopItemWidth();

        // Add spacing between the last slider and the close button
        ImGui::Spacing();

        // Center the close button
        ImGui::SetCursorPosX((popupWidth - ImGui::CalcTextSize("Close").x) * 0.5f);
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("QUIT", buttonSize)) {
		exit(0);
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Quit").x) * 0.5f);

    // Help button
    ImVec2 helpButtonSize(25, 25);
    ImGui::SetCursorPos(ImVec2(windowWidth - helpButtonSize.x - 10, ImGui::GetWindowHeight() - helpButtonSize.y - 10));
    
    if (ImGui::Button("?", helpButtonSize)) {
        showHelp = !showHelp;
    }

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Help");
    }

    ImGui::PopStyleVar();
    ImGui::End();
}

void renderHelpWindow() {
	if (!showHelp) return;

	ImGui::Begin("Help",&showHelp, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(600, 300));
    ImGui::SetWindowPos(ImVec2(80, 250));

    float defaultFontScale = ImGui::GetIO().FontGlobalScale;
    ImGui::SetWindowFontScale(1.2f);

    ImGui::Text("Objective:");
    ImGui::BulletText("Break all the blocks without letting the ball hit the ground.");

    ImGui::Spacing();
    ImGui::Text("\nControls:");
    ImGui::BulletText("Move the paddle left: A");
    ImGui::BulletText("Move the paddle right: D");
    ImGui::BulletText("Pause the game: Escape");

    ImGui::Spacing();
    ImGui::Text("\nGameplay:");
    ImGui::BulletText("Use the paddle to bounce the ball and break the blocks.");
    ImGui::BulletText("White blocks are multi-hit and require multiple hits to break.");
    ImGui::BulletText("Each block successfully broken awards 300 points.");
    ImGui::BulletText("Don't let the ball hit the ground, or you'll lose a life.");

    ImGui::Spacing();
    ImGui::Text("\nGood luck and have fun!");

	ImGui::SetWindowFontScale(defaultFontScale);
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
        resetGame = true;
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

void renderGameOverMenu() {
    if (!isGameOver) return;

    ImGui::Begin(":(", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(300, 200));
    ImGui::SetWindowPos(ImVec2(250, 250));

    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("GAME OVER").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text("\n\nGAME OVER");

    ImVec2 buttonSize(120, 30);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.5f);

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("TRY AGAIN", buttonSize)) {
        resetGame = true;
    }

    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Try Again").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.7f);

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("EXIT", buttonSize)) {
        exit(0);
    }

    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Exit").x) * 0.5f);

    ImGui::PopStyleVar();
    ImGui::End();
}