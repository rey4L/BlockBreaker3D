#include "boilerPlate.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "vertices.h"
#include "block.h"
#include "render.h"

int main() {
    initializeGLFW();
    GLFWwindow* window = createGLFWWindow(1280, 720, "BrickBreaker3D");
    if (!window)
        return -1;

    // Initialize shape state and set it as the window's user pointer
    PaddleState paddleState; // Make sure this persists in scope as long as it's needed
    glfwSetWindowUserPointer(window, &paddleState);

    glfwSetKeyCallback(window, key);
    initializeGLAD();

    // Specify the viewport of OpenGL in the Window
    setupViewport(1280, 720);

    // Compile shaders
    Shader shaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    // Calls to renderer
    // Two triangle square
    VBO VBO1(Vertices::square_cube_vertices, sizeof(Vertices::square_cube_vertices));
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
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 9; ++col) {
            cubes.emplace_back(glm::vec3(col * 0.5f - 0.5f, row * 0.5f + 0.8f, -3.0f), 0.70f);
        }
    }

    //second shape
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

    static double lastTime = glfwGetTime();

    // Main while loop
    while (!glfwWindowShouldClose(window)) {
        // Specify the color of the background
        glClearColor(r, g, b, 1.0f);

        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(x, y, z));
        proj = glm::perspective(glm::radians(30.0f), (float)(1280 / 720), 0.1f, 100.0f);

        // Outputs the matrices into the Vertex Shader
        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // Scale all axes by 50%
        glUniform1f(uniID, 0.45f);

        block.Bind();

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        // Iterate through cubes and render them
        for (auto& cube : cubes) {
            cube.render(shaderProgram, modelLoc, VAO1, Vertices::square_cube_indices, sizeof(Vertices::square_cube_indices));
        }
        
        // Clean this up
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
        PaddleProj = glm::perspective(glm::radians(45.0f), (float)(1000 / 1000), 0.1f, 100.0f);

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
    shaderProgram.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();

    return 0;
}