#include "interface.h"
#include "boilerPlate.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "vertices.h"
#include "block.h"
#include "render.h"
#include <iostream>
#include "audio.h"
#include <vector>
#include "particleSystem.h"

// Translation matrix values for the ball
float tra_x = 0.0f;
float tra_y = 0.0f;
float tra_z = -10.0f;

// Rotation matrix values for the ball
const float rot_x = 0.0f;
const float rot_y = 0.0f;
const float rot_z = 0.0f;

// Ball velocity
float ball_velocity_x = 5.0f;
float ball_velocity_y = 5.0f;
float ball_velocity_z = 0.0f;

// Paddle primitive arrays
std::vector<GLfloat> pill_vertices;
std::vector<GLuint> pill_indices;

// Paddle constants (collision related dimensions)
float paddleWidth = 0.60f; // percentage of the pill the ball sees
float paddleHeight = 0.25f;
float paddleDepth = 0.25;

// Set paddle radius and legth
float radius = 0.70f / 2;
float length = 2.25f;

// Controls the duration of the power-up notification
float messageTimer = 0.0f;
const float MESSAGE_DURATION = 2.5f;

// Ball speed & initial Y position
float ball_speed = 7.5f;
float position_y = -2.0f; 

// Define the game world boundaries
const float gameWorldMinX = -2.1f;
const float gameWorldMaxX = 3.2f;
const float gameWorldMinY = 1.5f;
const float gameWorldMaxY = 2.7f;
const float gameWorldZ = -10.0f;

// Calculate the block spacing and size
const float blockSpacingX = (gameWorldMaxX - gameWorldMinX) / 8.0f;
const float blockSpacingY = (gameWorldMaxY - gameWorldMinY) / 4.0f;
const float blockSize = 0.55f;

bool isTransitioning = false; // Flag to be used with timer upon game level reset

// Define an index to keep track of the current color
int currentColorIndex = 0; 
std::vector<Cube> cubes;

int points = 300; // Points per collision

// Define an array of colors for the cubes 
glm::vec3 cubeColors[12] = {
    glm::vec3(1.0f, 0.0f, 0.0f),   // Red
    glm::vec3(0.0f, 1.0f, 0.0f),   // Green
    glm::vec3(0.0f, 0.0f, 1.0f),   // Blue
    glm::vec3(1.0f, 1.0f, 0.0f),   // Yellow
    glm::vec3(1.0f, 0.0f, 1.0f),   // Magenta
    glm::vec3(0.0f, 1.0f, 1.0f),   // Cyan
    glm::vec3(1.0f, 0.5f, 0.0f),   // Orange
    glm::vec3(1.0f, 0.0f, 0.5f),   // Reddish-purple
    glm::vec3(0.5f, 0.0f, 1.0f),   // Bluish-purple
    glm::vec3(0.0f, 1.0f, 0.5f),   // Greenish-cyan
    glm::vec3(0.5f, 1.0f, 0.0f),   // Yellowish-green
    glm::vec3(0.0f, 0.5f, 1.0f),   // Blueish-cyan
};

// Define colors for each object changed
glm::vec3 cubeColor = glm::vec3(1.0, 0.0, 0.0); // Red changed 
glm::vec3 paddleColor = glm::vec3(1.275, 0.910, 0.706); // Green changed 
glm::vec3 ballColor = glm::vec3(1.300, 1.076, 1.800); // Blue changed

glm::vec3 lightPos(5.0f, 200.0f, -15.0f);  // changed 
glm::vec3 lightColor(1.0f, 1.0f, 1.0f); // changed
glm::vec3 ambientColor(0.2f, 0.2f, 0.2f); // changed 

float ambientStrength = 0.2f; // changed 
float specularStrength = 2.0f; // changed 
float shininess = 2.0f; // changed 

// PBR properties
float metallic = 3.25f;                          
float roughness = 0.0f;                         
float ao = 0.95f;


int main() {

    initializeGLFW();
    GLFWwindow* window = createGLFWWindow(760, 760, "BlockBreaker3D");
    if (!window)
        return -1;

    Audio audio;
    audio.playBackgroundMusic();

    // Initialize shape state and set it as the window's user pointer
    PaddleState paddleState; 
    glfwSetWindowUserPointer(window, &paddleState);

    glfwSetKeyCallback(window, key);
    initializeGLAD();

    setupViewport(750, 750);

    randomizeTrajectory(ball_speed);

    // Compile shaders
    Shader shaderProgram("default.vert", "default.frag");
    ParticleSystem particleSystem("particle.vert", "particle.frag");

    particleSystem.setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    VAO VAO1;
    VAO1.Bind();

    // Cube primitive initialization
    VBO VBO1(Vertices::cuboid_vertices, sizeof(Vertices::cuboid_vertices));
    EBO EBO1(Vertices::square_cube_indices, sizeof(Vertices::square_cube_indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Configure OpenGL state settings
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Paddle primitive initialization
    int numCylinderIndices = segments * 12;
    int numSphereIndices = segments * segments * 12;
    int totalIndices = numCylinderIndices + numSphereIndices;

    generatePillVertices(pill_vertices, radius, length);
    generatePillIndices(pill_indices);

    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(pill_vertices.data(), pill_vertices.size() * sizeof(float));
    EBO EBO2(pill_indices.data(), pill_indices.size() * sizeof(float));

    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();

    //-- Adding the sphere --//

    // Generate sphere vertices
    float sphereRadius = 0.30f;
    unsigned int longitudeCount = 1296; // More segments mean a smoother sphere
    unsigned int latitudeCount = 648;

    std::vector<float> sphereVertices;
    std::vector<unsigned int> sphereIndices;

    generateSphere(sphereRadius, longitudeCount, latitudeCount, sphereVertices, sphereIndices);

    VAO VAO3;
    VAO3.Bind();

    VBO VBO3(sphereVertices.data(), sphereVertices.size() * sizeof(float));
    EBO EBO3(sphereIndices.data(), sphereIndices.size() * sizeof(unsigned int));

    VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO3.Unbind();
    VBO3.Unbind();
    EBO3.Unbind();
    EBO3.Unbind();

    double lastTime = glfwGetTime(); // Used in deltaTime calculations later

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 7; ++col) {
            float normalizedX = gameWorldMinX + col * blockSpacingX + blockSpacingX / 2.0f;
            float normalizedY = gameWorldMinY + row * blockSpacingY + blockSpacingY / 2.0f;
            Cube cube(glm::vec3(normalizedX, normalizedY, gameWorldZ), blockSize, cubeColors[currentColorIndex]);
            currentColorIndex = (currentColorIndex + 1) % (sizeof(cubeColors) / sizeof(cubeColors[0]));
            cubes.push_back(cube);
        }
    }

    imguiInit(window);

    // Main while loop
    while (!glfwWindowShouldClose(window)) {
      
        colorBufferInit(r, g, b);
        glClearColor(r, g, b, 1.0f);

        shaderProgram.Activate();

        int objectColorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor");

        // -- Block related code --
        glm::mat4 model;
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(x, y, z));
        proj = glm::perspective(glm::radians(30.0f), (float)(750 / 750), 0.1f, 100.0f);

        // Outputs the matrices into the Vertex Shader
        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // Scale all axes by 65%
        glUniform1f(uniID, 0.5f);

        VAO1.Bind();

        // Iterate through cubes and render them
        for (auto& cube : cubes) {
            if (!cube.isDestroyed) {
                glUniform3fv(objectColorLoc, 1, glm::value_ptr(cube.color));
                cube.render(shaderProgram, modelLoc, VAO1, Vertices::square_cube_indices, sizeof(Vertices::square_cube_indices));
            }
        }

        // -- Paddle related code --
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        
        PaddleState* paddleState = reinterpret_cast<PaddleState*>(glfwGetWindowUserPointer(window));
        
        // Set paddle color uniform
        glUniform3fv(objectColorLoc, 1, glm::value_ptr(paddleColor));

        // Paddle object location manipulation
        glm::mat4 PaddleModel = glm::mat4(1.0f);
        glm::mat4 PaddleView = glm::mat4(1.0f);
        glm::mat4 PaddleProj = glm::mat4(1.0f);

        if (paddleState == nullptr) {
            exit(EXIT_FAILURE);
        }

        glm::vec3 paddlePos = glm::vec3(paddleState->x_pos, paddleState->y_pos, paddleState->z_pos);

        // Translate the paddle
        PaddleView = glm::translate(PaddleView, paddlePos);
        PaddleProj = glm::perspective(glm::radians(30.0f), (float)(750 / 750), 1.1f, 100.0f);

        int PaddleModelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(PaddleModelLoc, 1, GL_FALSE, glm::value_ptr(PaddleModel));

        int PaddleViewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(PaddleViewLoc, 1, GL_FALSE, glm::value_ptr(PaddleView));

        int PaddleProjLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(PaddleProjLoc, 1, GL_FALSE, glm::value_ptr(PaddleProj));

        updatePaddlePosition(paddleState, deltaTime, particleSystem);
        particleSystem.update(deltaTime);
        particleSystem.draw(PaddleView, PaddleProj);

        VAO2.Bind();
        glDrawElements(GL_TRIANGLES, totalIndices, GL_UNSIGNED_INT, 0);

        // -- Sphere related code --
        glm::vec3 spherePosition = glm::vec3(tra_x, position_y, tra_z);

        glm::mat4 sphereModel = glm::mat4(1.0f);
        glm::mat4 sphereView = glm::mat4(1.0f);
        glm::mat4 sphereProj = glm::mat4(1.0f);

        // Set ball color uniform
        glUniform3fv(objectColorLoc, 1, glm::value_ptr(ballColor)); //changed

        // Set lighting uniforms
        int lightPosLoc = glGetUniformLocation(shaderProgram.ID, "lightPos");
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

        int lightColorLoc = glGetUniformLocation(shaderProgram.ID, "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

        int viewPosLoc = glGetUniformLocation(shaderProgram.ID, "viewPos");
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(glm::vec3(tra_x, position_y, tra_z))); // Assuming the camera follows the ball

        int ambientColorLoc = glGetUniformLocation(shaderProgram.ID, "ambientColor");
        glUniform3fv(ambientColorLoc, 1, glm::value_ptr(ambientColor));

        int ambientStrengthLoc = glGetUniformLocation(shaderProgram.ID, "ambientStrength");
        glUniform1f(ambientStrengthLoc, ambientStrength);

        int specularStrengthLoc = glGetUniformLocation(shaderProgram.ID, "specularStrength");
        glUniform1f(specularStrengthLoc, specularStrength);

        int shininessLoc = glGetUniformLocation(shaderProgram.ID, "shininess");
        glUniform1f(shininessLoc, shininess);

        // Retrieve uniform locations
        GLint metallicLoc = glGetUniformLocation(shaderProgram.ID, "metallic");
        GLint roughnessLoc = glGetUniformLocation(shaderProgram.ID, "roughness");
        GLint aoLoc = glGetUniformLocation(shaderProgram.ID, "ao");

        glUniform1f(metallicLoc, metallic);
        glUniform1f(roughnessLoc, roughness);
        glUniform1f(aoLoc, ao);

        sphereView = glm::translate(sphereView, spherePosition);
        sphereProj = glm::perspective(glm::radians(30.0f), (float)(750 / 750), 0.1f, 100.0f);

        int sphereModelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(sphereModelLoc, 1, GL_FALSE, glm::value_ptr(sphereModel));

        int sphereViewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(sphereViewLoc, 1, GL_FALSE, glm::value_ptr(sphereView));

        int sphereProjLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(sphereProjLoc, 1, GL_FALSE, glm::value_ptr(sphereProj));


        // Start ImGui frame
        imguiNewFrame();

        if (showMenu || showHelp) {
            renderMenu();
            renderHelpWindow();
            audio.setBackgroundMusicVolume(backgroundMusicVolume);
            audio.setSoundEffectsVolume(soundEffectsVolume);
        }

        else if (isPaused) {

            renderPauseMenu();

            if (resetGame) {
                score = 0;
                audio.stopBackgroundMusic();
                resetGameState(audio); 
                
                // Re render paddle with default dimensions
                VBO2.Update(pill_vertices.data(), pill_vertices.size() * sizeof(float));
                resetGame = false;
            }
        }

        else if (isGameOver) {
            renderGameOverMenu();

            if (resetGame) {
                score = 0;
                resetGameState(audio);

                VBO2.Update(pill_vertices.data(), pill_vertices.size() * sizeof(float));
                resetGame = false;
            }
        }

        else {

            updateScore(); // Imgui score overlay
            
            if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
                isPaused = true;
            }

            updateBallPosition(tra_x, position_y, tra_z, ball_velocity_x, ball_velocity_y, ball_velocity_z,
                deltaTime, audio, isGameOver);

            glm::vec3 velocity = glm::vec3(ball_velocity_x, ball_velocity_y, ball_velocity_z);
            
            handlePaddleCollision(spherePosition, velocity, paddlePos,
                sphereRadius, ball_velocity_x, ball_velocity_y,
                ball_velocity_z, audio, paddleWidth, paddleHeight, paddleDepth);

            for (auto& cube : cubes) {

                if (!cube.isDestroyed && cube.collidesWith(spherePosition, sphereRadius)) {
                    cube.isDestroyed = true;
                    audio.playCollisionSound();
                    incrementScore(points);

                    // Calculate the collision normal
                    glm::vec3 collisionNormal = glm::normalize(spherePosition - cube.position);

                    // Calculate power-up likelihood on collision
                    applyPowerUp(cubes, paddleWidth, length, audio);
                    VBO2.Update(pill_vertices.data(), pill_vertices.size() * sizeof(float));

                    // Reflect the velocity of the sphere based on the collision normal
                    glm::vec3 reflectedVelocity = glm::reflect(velocity, collisionNormal);
                    ball_velocity_x = reflectedVelocity.x;
                    ball_velocity_y = reflectedVelocity.y;
                    ball_velocity_z = reflectedVelocity.z;
                }
            }

            if (showPowerUp) {
                showPowerUpMessage(deltaTime); // Notify user when they trigger a power-up
            }

            // Render new blocks when all current blocks are destroyed
            bool allBlocksDestroyed = areAllBlocksDestroyed(cubes);
            if (allBlocksDestroyed) {
                audio.playResetSound();
                resetGameState(audio);
                resetGame = false;
            }
        }

        VAO3.Bind();
        glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
  
    // Cleanup
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();
    VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();
    shaderProgram.Delete();

    imguiCleanup();
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}