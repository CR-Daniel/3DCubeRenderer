// Including necessary libraries
#include <GL/glew.h>    // GLEW (OpenGL Extension Wrangler Library) helps in querying and loading OpenGL extensions
#include <GLFW/glfw3.h> // GLFW is a library to help with creating windows and contexts, handling input, etc.
#include <glm/glm.hpp>  // GLM (OpenGL Mathematics) is a math library designed for graphics software
#include <glm/gtc/matrix_transform.hpp>  // Useful for transforming matrices
#include <glm/gtc/type_ptr.hpp>  // Allows us to send matrices to shaders

// Vertex shader source code
const char* vertexShaderSource = R"glsl(
    // Specifying the version of GLSL (OpenGL Shading Language)
    #version 330 core  
    // Input vertex attributes (in this case, only position)
    layout (location = 0) in vec3 aPos;  

    // Transformation matrices
    uniform mat4 model;  
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        // Convert the 3D position of the vertex for 2D drawing
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
)glsl";

// Fragment shader source code
const char* fragmentShaderSource = R"glsl(
    #version 330 core
    // Output color of the fragment
    out vec4 FragColor;

    void main()
    {
        // Set the fragment color
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)glsl";

// Function to compile and link shaders, then return the shader program ID
GLuint createShaderProgram() {
    // Create, compile and check the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create, compile and check the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders to create a shader program and return its ID
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up individual shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a GLFW window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewInit();

    // Cube vertices data
    float vertices[] = { 
        // positions         
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    // Generate and bind VAO (Vertex Array Object) and VBO (Vertex Buffer Object)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and send data to GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Specify how OpenGL should interpret our vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the buffer and vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Enable depth testing to ensure correct depth perception
    glEnable(GL_DEPTH_TEST);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create shader program
        GLuint shaderProgram = createShaderProgram();
        glUseProgram(shaderProgram);

        // Create transformation matrices
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        // Send matrices to the shader
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Swap the screen buffers
        glfwSwapBuffers(window);
        // Poll for any input events
        glfwPollEvents();

        // Delete the shader program to avoid memory leak
        glDeleteProgram(shaderProgram);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
