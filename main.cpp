#include "interface.h"
#include "boilerPlate.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "vertices.h"
#include "block.h"
#include "render.h"
#include <iostream>
#include "audio.h"
#include <random> // Add this header for random number generation


// Translation matrix values for the ball
float tra_x = 0.0f;
float tra_y = 0.35f;
float tra_z = -10.0f; // z-value of the scene and paddle + z-value of the blocks;

// Rotation matrix values for the ball
const float rot_x = 0.0f;
const float rot_y = 0.0f;
const float rot_z = 1.0f;

std::vector <unsigned int> paddle_indices;
std::vector <float> paddle_vertices;

// Function to apply a power-up to a random block
void applyPowerUp(std::vector<Cube>& cubes) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cubes.size() - 1);

    int randomIndex = dis(gen);

    if (!cubes[randomIndex].isDestroyed) {
        // Apply power-up logic here
        cubes[randomIndex].color = glm::vec3(1.0f, 1.0f, 1.0f); // White
    }
}


int main() {
 
    initializeGLFW();
    GLFWwindow* window = createGLFWWindow(750, 750, "BrickBreaker3D");
    if (!window)
        return -1;

    Audio audio;
    audio.playBackgroundMusic();
  
    // Initialize shape state and set it as the window's user pointer
    PaddleState paddleState; // Make sure this persists in scope as long as it's needed
    glfwSetWindowUserPointer(window, &paddleState);

    glfwSetKeyCallback(window, key);
    initializeGLAD();

    // Specify the viewport of OpenGL in the Window
    setupViewport(750, 750);

    // Compile shaders
    Shader shaderProgram("default.vert", "default.frag");
    Shader modelShader("model.vert", "model.frag");

    VAO VAO1;
    VAO1.Bind();

    // Cube primitive initialization
    VBO VBO1(Vertices::cuboid_vertices, sizeof(Vertices::cuboid_vertices));
    EBO EBO1(Vertices::square_cube_indices, sizeof(Vertices::square_cube_indices));

    // Requisite method calls
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Texture initialization
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    Texture block("block-tex.png", GL_TEXTURE_2D, GL_REPEAT, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    block.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    // Paddle primitive initialization
    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(Vertices::cuboid_vertices, sizeof(Vertices::cuboid_vertices));
    EBO EBO2(Vertices::square_cube_indices, sizeof(Vertices::square_cube_indices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	// Texture initialization
    Texture cuboid("blue-neon.png", GL_TEXTURE_2D, GL_REPEAT, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cuboid.texUnit(shaderProgram, "tex0", 0);

    //-- Adding the sphere --//

    // Generate sphere vertices
    float sphereRadius = 0.25f;
    unsigned int longitudeCount = 1296; // More segments mean a smoother sphere
    unsigned int latitudeCount = 648;
    std::vector<float> sphereVertices;
    std::vector<unsigned int> sphereIndices;
    generateSphere(sphereRadius, longitudeCount, latitudeCount, sphereVertices, sphereIndices);

	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(sphereVertices.data(), sphereVertices.size() * sizeof(float));
	EBO EBO3(sphereIndices.data(), sphereIndices.size() * sizeof(unsigned int));

    //Link vertex attributes
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

    // Texture initialization
    Texture sphere("circle.jpg", GL_TEXTURE_2D, GL_REPEAT, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	sphere.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    // Rotation parameters (will be removed later)
    float rotation = 0.0f;

    // Bouncing constants
    float position_y = 1.0f; // Initial Y position
    float groundLevel = -2.7f; // Y position of the ground;

    double lastTime = glfwGetTime();

    // Ball velocity
    float ball_velocity_x = 5.0f;
    float ball_velocity_y = 5.0f;
    float ball_velocity_z = 0.0f;

    // Scene boundaries
    float left_boundary = -2.5f;
    float right_boundary = 2.5f;
    float top_boundary = 2.5f;
    float bottom_boundary = -2.0f;
    float front_boundary = -15.0f;
    float back_boundary = -5.0f;

    // Define an array of colors for the cubes changed 
    glm::vec3 cubeColors[] = {
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

    // Define an index to keep track of the current color
    int currentColorIndex = 0; //changed

    std::vector<Cube> cubes;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 8; ++col) {
            Cube cube(glm::vec3(col * 0.7f - 3.4f, row * 0.3f + 1.8f, -10.0f), 0.45f, cubeColors[currentColorIndex]);
            currentColorIndex = (currentColorIndex + 1) % (sizeof(cubeColors) / sizeof(cubeColors[0]));
            cubes.push_back(cube);
        }
    }
   
    //Initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    // Main while loop
    while (!glfwWindowShouldClose(window)) {
        // Specify the color of the background
        glClearColor(r, g, b, 1.0f);

        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        

        // Define colors for each object changed
        glm::vec3 cubeColor = glm::vec3(1.0, 0.0, 0.0); // Red changed 
        glm::vec3 paddleColor = glm::vec3(0.0, 1.0, 0.0); // Green changed 
        glm::vec3 ballColor = glm::vec3(0.0, 0.0, 1.0); // Blue changed

        glm::vec3 lightPos(1.0f, 2.0f, 2.0f);  // changed 
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f); // changed 
        glm::vec3 ambientColor(0.2f, 0.2f, 0.2f); // changed 
        float ambientStrength = 0.3f; // changed 
        float specularStrength = 0.5f; // changed 
        float shininess = 64.0f; // changed 


        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        // Set object color uniforms changed
        int objectColorLoc = glGetUniformLocation(shaderProgram.ID, "objectColor"); //changed

        // -- Block related code --
        glm::mat4 model = glm::mat4(1.0f); 
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


        // Scale all axes by 50%
        glUniform1f(uniID, 0.65f);

        block.Bind();

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        // Iterate through cubes and render them
        for (auto& cube : cubes) {
            if (!cube.isDestroyed) {
                glUniform3fv(objectColorLoc, 1, glm::value_ptr(cube.color));
                cube.render(shaderProgram, modelLoc, VAO1, Vertices::square_cube_indices, sizeof(Vertices::square_cube_indices));
            }
        }

        // Check for collision between the sphere and the blocks
        //for (auto& cube : cubes) {
        //    if (!cube.isDestroyed && cube.collidesWith(glm::vec3(tra_x, position_y, tra_z), sphereRadius)) {
        //        cube.isDestroyed = true;
        //        //velocity_y = -velocity_y; // Reverse the velocity of the sphere

        //        // Calculate the collision normal
        //        glm::vec3 collisionPoint = glm::vec3(tra_x, position_y, tra_z);
        //        glm::vec3 collisionNormal = glm::normalize(glm::vec3(tra_x, position_y, tra_z) - cube.position);

        //        // Adjust the ball's position to prevent penetration
        //        const float penetrationDepth = sphereRadius - glm::length(collisionPoint - cube.position);
        //        tra_x += collisionNormal.x * penetrationDepth;
        //        position_y += collisionNormal.y * penetrationDepth;
        //        tra_z += collisionNormal.z * penetrationDepth;

        //        // Reflect the velocity of the sphere based on the collision normal
        //        glm::vec3 reflectedVelocity = glm::reflect(glm::vec3(ball_velocity_x, ball_velocity_y, ball_velocity_z), collisionNormal);
        //        ball_velocity_x = reflectedVelocity.x;
        //        ball_velocity_y = reflectedVelocity.y;
        //        ball_velocity_z = reflectedVelocity.z;

        //        cube.isDestroyed = true;
        //    }
        //}
        
        // -- Paddle related code --
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        PaddleState* paddleState = reinterpret_cast<PaddleState*>(glfwGetWindowUserPointer(window));
        updatePaddlePosition(paddleState, deltaTime);

        // Set paddle color uniform
        glUniform3fv(objectColorLoc, 1, glm::value_ptr(paddleColor));

        // Paddle object location manipulation
        glm::mat4 PaddleModel = glm::mat4(1.0f);
        glm::mat4 PaddleView = glm::mat4(1.0f);
        glm::mat4 PaddleProj = glm::mat4(1.0f);

        if (paddleState == nullptr) {
            exit(EXIT_FAILURE);
        }
        
        // Translate the paddle
        PaddleView = glm::translate(PaddleView, glm::vec3(paddleState->x_pos, paddleState->y_pos, paddleState->z_pos));
        PaddleProj = glm::perspective(glm::radians(30.0f), (float)(750 / 750), 0.1f, 100.0f);

        // Outputs the matrices into the Vertex Shader
        int PaddleModelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(PaddleModelLoc, 1, GL_FALSE, glm::value_ptr(PaddleModel));

        int PaddleViewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(PaddleViewLoc, 1, GL_FALSE, glm::value_ptr(PaddleView));

        int PaddleProjLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(PaddleProjLoc, 1, GL_FALSE, glm::value_ptr(PaddleProj));

        cuboid.Bind();
        VAO2.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // -- Sphere related code --
        double crntTime = glfwGetTime();

        glm::mat4 sphereModel = glm::mat4(1.0f);
		glm::mat4 sphereView = glm::mat4(1.0f);
		glm::mat4 sphereProj = glm::mat4(1.0f);

        // Set ball color uniform
        glUniform3fv(objectColorLoc, 1, glm::value_ptr(ballColor)); //changed


		sphereModel = glm::rotate(sphereModel, glm::radians(rotation), glm::vec3(rot_x, rot_y, rot_z));
        sphereView = glm::translate(sphereView, glm::vec3(tra_x, position_y, tra_z));
        sphereProj = glm::perspective(glm::radians(30.0f), (float)(750 / 750), 0.1f, 100.0f);

        int sphereModelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(sphereModelLoc, 1, GL_FALSE, glm::value_ptr(sphereModel));

        int sphereViewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(sphereViewLoc, 1, GL_FALSE, glm::value_ptr(sphereView));

        int sphereProjLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(sphereProjLoc, 1, GL_FALSE, glm::value_ptr(sphereProj));

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (showMenu) {
            renderMenu();
            audio.setBackgroundMusicVolume(backgroundMusicVolume);
            audio.setSoundEffectsVolume(soundEffectsVolume);
        }
        else {
            if (isPaused) {
                renderPauseMenu();
            }
            else {

                if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_P))) {
                    isPaused = true;
                }

                // Update ball position
                tra_x += ball_velocity_x * deltaTime;
                position_y += ball_velocity_y * deltaTime;
                tra_z += ball_velocity_z * deltaTime;

                // Check for collisions with scene boundaries
                if (tra_x <= left_boundary || tra_x >= right_boundary) {
                    ball_velocity_x = -ball_velocity_x;
                    
                }
                if (position_y <= bottom_boundary || position_y >= top_boundary) {
                    ball_velocity_y = -ball_velocity_y;
                }
                if (tra_z <= front_boundary || tra_z >= back_boundary) {
                    ball_velocity_z = -ball_velocity_z;
                }


                for (auto& cube : cubes) {
                   
                    if (!cube.isDestroyed && cube.collidesWith(glm::vec3(tra_x, position_y, tra_z), sphereRadius)) {
                        cube.isDestroyed = true;
                        audio.playCollisionSound();
                        // Calculate the collision normal
                        glm::vec3 collisionNormal = glm::normalize(glm::vec3(tra_x, position_y, tra_z) - cube.position);

                        // Inside the game loop
                        applyPowerUp(cubes);

                        // Reflect the velocity of the sphere based on the collision normal
                        glm::vec3 reflectedVelocity = glm::reflect(glm::vec3(ball_velocity_x, ball_velocity_y, ball_velocity_z), collisionNormal);
                        ball_velocity_x = reflectedVelocity.x;
                        ball_velocity_y = reflectedVelocity.y;
                        ball_velocity_z = reflectedVelocity.z;
                      
                       
                    }
                }
            }
        }

        sphere.Bind();
		VAO3.Bind();
        glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();

      
    }
  
    // Delete all objects created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    block.Delete();
    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();
    cuboid.Delete();
    VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();
	sphere.Delete();
    shaderProgram.Delete();
    modelShader.Delete();

    // Cleanup Dear ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
 
    // Delete window before ending the program
    glfwDestroyWindow(window);
 
    // Terminate GLFW before ending the program
    glfwTerminate();

    return 0;
}