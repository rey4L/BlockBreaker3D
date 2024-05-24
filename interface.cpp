#include "interface.h"

bool showMenu = true;
bool isPaused = false;
bool isGameOver = false; 
bool resetGame = false;
bool showHelp = false;
bool showPowerUp = false;
bool showCountdown = false;

int score = 0;

float backgroundMusicVolume = 0.25f;
float soundEffectsVolume = 0.40f;

void imguiInit(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImFont* myFont = io.Fonts->AddFontFromFileTTF("font/Minecraft.ttf", 15.0f); // Custom font
    io.FontDefault = myFont;
}

void imguiNewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void renderMenu() {
    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(380, 250));
    ImGui::SetWindowPos(ImVec2(190, 260));

    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Lighter blue when hovered
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.45f, 0.0f, 1.0f)); // Green when pressed

    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("Welcome to Brick Breaker 3D!").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.3f);
    ImGui::Text("\n\nWELCOME TO BLOCK BREAKER 3D!");

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.4f);

    ImVec2 buttonSize(120, 30);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("PLAY", buttonSize)) {
        showMenu = false;
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Start Game").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.55f);

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("SOUND", buttonSize)) {
        ImGui::OpenPopup("Sound Settings");
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Sound").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.7f);

    // Sound settings window
    if (ImGui::BeginPopupModal("Sound Settings", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
        
        float popupWidth = 400.0f;
        ImGui::SetWindowSize(ImVec2(popupWidth, 175.0f));
        ImGui::SetWindowPos(ImVec2(170.0f, 300.0f));

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        // Background Music Volume Slider
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.25f); 
        ImGui::Text("Background Music Volume");
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.25f); 
        ImGui::PushItemWidth(300.0f);
        int bgVolumePercent = static_cast<int>(backgroundMusicVolume * 100.0f);
        ImGui::SliderInt("##bgVolume", &bgVolumePercent, 0, 100, "%d%%");
        backgroundMusicVolume = bgVolumePercent / 100.0f;
        
        ImGui::PopItemWidth();

        ImGui::Spacing();
        ImGui::Spacing();

        // Sound Effects Volume Slider
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.25f); 
        ImGui::Text("Sound Effects Volume");
        ImGui::SetCursorPosX((popupWidth - 200.0f) * 0.25f); 
        ImGui::PushItemWidth(300.0f);
        int sfxVolumePercent = static_cast<int>(soundEffectsVolume * 100.0f);
        ImGui::SliderInt("##sfxVolume", &sfxVolumePercent, 0, 100, "%d%%");
        soundEffectsVolume = sfxVolumePercent / 100.0f;
        ImGui::PopItemWidth();

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImVec2 buttonSize(60, 20);

        // Center the close button
        ImGui::SetCursorPosX((popupWidth - buttonSize.x) * 0.9f);
        if (ImGui::Button("Close", buttonSize)) {
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
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.65f, 0.3f, 1.0f));
    if (ImGui::Button("?", helpButtonSize)) {
        showHelp = !showHelp;
    }

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Help");
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::End();
}

void renderHelpWindow() {
	if (!showHelp) return;

    ImVec4 closeButtonHoverColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red color for hover
    ImVec4 closeButtonActiveColor = ImVec4(0.8f, 0.0f, 0.0f, 1.0f); // Darker red for active

    // Backup the style colors
    ImVec4 oldButtonHoveredColor = ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered];
    ImVec4 oldButtonActiveColor = ImGui::GetStyle().Colors[ImGuiCol_ButtonActive];

    // Set the new style colors
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, closeButtonHoverColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, closeButtonActiveColor);

	ImGui::Begin("Help",&showHelp, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(635, 415));
    ImGui::SetWindowPos(ImVec2(63, 175));

    float defaultFontScale = ImGui::GetIO().FontGlobalScale;
    ImGui::SetWindowFontScale(1.2f);

    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Objective:");
    ImGui::Text("Break all blocks without letting the ball hit the ground.\n");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Controls:");
    ImGui::BulletText("Paddle left: A");
    ImGui::BulletText("Paddle right: D");
    ImGui::BulletText("Pause: Escape");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Gameplay:");
    ImGui::BulletText("Use the paddle to bounce the ball and break blocks.");
    ImGui::BulletText("Some blocks (white ones) have a 2%% chance of granting a powerup.");
    ImGui::BulletText("Each block awards 300 points when broken.");
    ImGui::BulletText("Don't let the ball hit the ground.");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7523f, 0.343f, 0.0f, 1.0f));
    ImGui::TextWrapped("Note: \n1. Do not press A and D simultaneously as it will result in no movement.\n2. When your paddle lenght increases so does the ball speed.");
    ImGui::PopStyleColor(3);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(0.0f, 0.8f, 0.0f, 1.0f), "Good luck and have fun!");

	ImGui::SetWindowFontScale(defaultFontScale);
    ImGui::End();
}

void renderPauseMenu() {
    ImGui::Begin("Pause Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(320, 280));
    ImGui::SetWindowPos(ImVec2(215, 250));

    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Gray when hovered
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.45f, 0.0f, 1.0f)); // Green when pressed

    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("Game Paused").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text("\n\nGAME PAUSED");

    // Set button size
    ImVec2 buttonSize(120, 30);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.4f); 

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("RESUME", buttonSize)) {
        isPaused = false;
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Resume").x) * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.55f); 

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("RESTART", buttonSize)) {
        resetGame = true;
    }
    ImGui::SetCursorPosX(windowWidth - ImGui::CalcTextSize("Restart").x * 0.5f);

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.7f); 

    ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);
    if (ImGui::Button("MAIN MENU", buttonSize)) {
        isPaused = false;
        resetGame = true;
        showMenu = true;
    }
    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Main Menu").x) * 0.5f);

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);
    ImGui::End();
}

void updateScore() {
    ImGui::Begin("Score", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SetWindowPos(ImVec2(5, 10));
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Score: %d", score);
    ImGui::End();
}

void showPowerUpMessage(float deltaTime) {
    if (!showPowerUp) {
        messageTimer = 0.0f;
        return;
    }

    messageTimer += deltaTime;

    if (messageTimer >= MESSAGE_DURATION) {
        showPowerUp = false;
        return;
    }
        ImGui::SetNextWindowPos(ImVec2(760 / 2, 760 / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowBgAlpha(0.8f);
        ImGui::Begin("Power-Up Message", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255)); 
        ImGui::Text("Power-Up Triggered!");
        ImGui::Text("Your paddle size has increased!");
        ImGui::PopStyleColor();

        ImGui::End();
}

void showCountdownMessage(float deltaTime) {
    if (!showCountdown) return;

    countdownTimer += deltaTime;

    // Update the countdown value
    if (countdownTimer >= COUNTDOWN_DURATION) {
        countdownTimer = 0.0f;
        countdownValue--;
        if (countdownValue < 0) {
            showCountdown = false;
            countdownValue = 3;
            return;
        }
    }

    // Calculate fade effect
    float alpha = 1.0f;
    if (countdownTimer >= COUNTDOWN_DURATION - MESSAGE_FADE_DURATION) {
        alpha = (COUNTDOWN_DURATION - countdownTimer) / MESSAGE_FADE_DURATION;
    }

    // Render the countdown message
    ImGui::SetNextWindowPos(ImVec2(760 / 2, 760 / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowBgAlpha(alpha);
    ImGui::Begin("Countdown Message", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

    
    if (countdownValue > 0) {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
        ImGui::Text("%d", countdownValue);
        ImGui::PopStyleColor();
    }
    else {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
        ImGui::Text("GO!");
        ImGui::PopStyleColor();
    }

    ImGui::End();
}

void renderGameOverMenu() {
    if (!isGameOver) return;

    ImGui::Begin("Game Over Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(300, 200));
    ImGui::SetWindowPos(ImVec2(225, 270));

    float windowWidth = ImGui::GetWindowSize().x;
    
    float textWidth = ImGui::CalcTextSize("GAME OVER").x;
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.20f);
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
    ImGui::Text("GAME OVER");
	ImGui::PopStyleColor();

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.330f);
    float scoreWidth = ImGui::CalcTextSize("Final score:").x;
    ImGui::SetCursorPosX((windowWidth - scoreWidth) * 0.40f);
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Final Score: %d", score);

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

void imguiCleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}