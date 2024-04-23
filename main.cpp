#include "boilerPlate.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "vertices.h"
#include "block.h"
#include "render.h"
#include "importer.h"

// Translation matrix values for the ball
const float tra_x = 0.0f;
const float tra_y = 0.0f;
const float tra_z = -10.0f; // z-value of the scene and paddle + z-value of the blocks;

// Rotation matrix values for the ball
const float rot_x = 0.0f;
const float rot_y = 0.0f;
const float rot_z = 1.0f;

std::vector <unsigned int> paddle_indices;
std::vector <float> paddle_vertices;

int main() {
    initializeGLFW();
    GLFWwindow* window = createGLFWWindow(750, 750, "BrickBreaker3D");
    if (!window)
        return -1;

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

    std::vector<Cube> cubes;
    // Populate your cubes vector
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 8; ++col) {
            cubes.emplace_back(glm::vec3(col * 0.7f - 3.4f, row * 0.3f + 1.8f, -10.0f), 0.45f);
        }
    }

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

    // Adding the sphere

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

    // Load model
    loadModelFromFile("path", paddle_vertices, paddle_indices);

    VAO VAO4;
	VAO4.Bind();

	VBO VBO4(paddle_vertices.data(), paddle_vertices.size() * sizeof(float));
	EBO EBO4(paddle_indices.data(), paddle_indices.size() * sizeof(unsigned int));

	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

    Texture obj("block-tex.png", GL_TEXTURE_2D, GL_REPEAT, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    obj.texUnit(modelShader, "diffuseMap", 0);

    glEnable(GL_DEPTH_TEST);

    // Rotation parameters
    float rotation = 0.0f;
    double prevTime = glfwGetTime();
    const float rotationSpeed = 1.5f;
    const double timeInterval = 1.0 / 120.0;

    // Bouncing constants
    float position_y = 0.0f; // Initial Y position
    float velocity_y = 7.5f; // Initial velocity upwards
    float gravity = -9.8f; // Gravity pulling down
    float groundLevel = -2.7f; // Y position of the ground
    float damping = 0.9f; // To simulate energy loss on bounce
    double deltaTime = 0; // Time difference between frames
    float minVelocity = -2.0f; // Minimum velocity threshold
    int bounceCount = 0;
    const int maxBounces = 70;

    double lastTime = glfwGetTime();

    // Main while loop
    while (!glfwWindowShouldClose(window)) {
        // Specify the color of the background
        glClearColor(r, g, b, 1.0f);

        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

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

        // Scale all axes by 50%
        glUniform1f(uniID, 0.65f);

        block.Bind();

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        // Iterate through cubes and render them
        for (auto& cube : cubes) {
            if (!cube.isDestroyed) {
                cube.render(shaderProgram, modelLoc, VAO1, Vertices::square_cube_indices, sizeof(Vertices::square_cube_indices));
            }
        }

        // Check for collision between the sphere and the blocks
        for (auto& cube : cubes) {
            if (!cube.isDestroyed && cube.collidesWith(glm::vec3(tra_x, position_y, tra_z), sphereRadius)) {
                cube.isDestroyed = true;
                velocity_y = -velocity_y; // Reverse the velocity of the sphere
            }
        }
        
        // -- Paddle related code --
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        PaddleState* paddleState = reinterpret_cast<PaddleState*>(glfwGetWindowUserPointer(window));
        updatePaddlePosition(paddleState, deltaTime);

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
        bounce(crntTime, prevTime, gravity, position_y, velocity_y, damping, groundLevel, minVelocity, bounceCount, maxBounces);
        updateRotation(rotation, prevTime, crntTime, rotationSpeed, timeInterval);

        glm::mat4 sphereModel = glm::mat4(1.0f);
		glm::mat4 sphereView = glm::mat4(1.0f);
		glm::mat4 sphereProj = glm::mat4(1.0f);

		sphereModel = glm::rotate(sphereModel, glm::radians(rotation), glm::vec3(rot_x, rot_y, rot_z));
        sphereView = glm::translate(sphereView, glm::vec3(tra_x, position_y, tra_z));
        sphereProj = glm::perspective(glm::radians(30.0f), (float)(750 / 750), 0.1f, 100.0f);

        int sphereModelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(sphereModelLoc, 1, GL_FALSE, glm::value_ptr(sphereModel));

        int sphereViewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(sphereViewLoc, 1, GL_FALSE, glm::value_ptr(sphereView));

        int sphereProjLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(sphereProjLoc, 1, GL_FALSE, glm::value_ptr(sphereProj));

        sphere.Bind();
		VAO3.Bind();
        glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

        // -- Object related code --

        //modelShader.Activate();

        //glm::mat4 ObjModel = glm::mat4(1.0f);
        //glm::mat4 ObjView = glm::mat4(1.0f);
        //glm::mat4 ObjProj = glm::mat4(1.0f);

        //ObjView = glm::translate(ObjView, glm::vec3(1.7f, 0.75f, -25.0f));
        //ObjProj = glm::perspective(glm::radians(30.0f), (float)(750 / 750), 0.1f, 100.0f);

        //// Outputs the matrices into the Vertex Shader
        //int ObjModelLoc = glGetUniformLocation(modelShader.ID, "model");
        //glUniformMatrix4fv(ObjModelLoc, 1, GL_FALSE, glm::value_ptr(ObjModel));

        //int ObjViewLoc = glGetUniformLocation(modelShader.ID, "view");
        //glUniformMatrix4fv(ObjViewLoc, 1, GL_FALSE, glm::value_ptr(ObjView));

        //int ObjProjLoc = glGetUniformLocation(modelShader.ID, "projection");
        //glUniformMatrix4fv(ObjProjLoc, 1, GL_FALSE, glm::value_ptr(ObjProj));

        //obj.Bind();
        //VAO4.Bind();
        //glDrawElements(GL_TRIANGLES, paddle_indices.size(), GL_UNSIGNED_INT, 0);

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
	VAO4.Delete();
	VBO4.Delete();
	EBO4.Delete();
	obj.Delete();
    shaderProgram.Delete();
    modelShader.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();

    return 0;
}