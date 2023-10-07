// Including necessary libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Vertex Shader: This shader will process each vertex and basically puts them in position.
const char* vertexShaderSource = R"glsl(
    #version 330 core                    // Version of GLSL.
    layout (location = 0) in vec2 aPos;  // Input vertex position.

    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);  // Setting the final vertex position.
    }
)glsl";

// Fragment Shader: This shader will color each pixel fragment.
const char* fragmentShaderSource = R"glsl(
    #version 330 core
    out vec4 FragColor;                   // Output color of the pixel.

    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);  // Setting the color to orange.
    }
)glsl";

// Function to create a shader program.
GLuint createShaderProgram() {
    // Creating the vertex shader and setting its source.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Creating the fragment shader and setting its source.
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Creating a shader program and attaching both shaders, then linking them.
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up individual shaders as they're now linked into the program.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram; // Return the linked shader program.
}

int main() {
    // Initialize GLFW.
    if (!glfwInit()) {
        return -1;
    }

    // Create a GLFW window of size 800x600.
    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Square", NULL, NULL);
    if (!window) {
        glfwTerminate(); // Terminate GLFW if window creation fails.
        return -1;
    }

    // Make the window the current context.
    glfwMakeContextCurrent(window);
    // Initialize GLEW.
    glewInit();

    // Define vertices for a square. Since it's 2D, we only need x and y.
    float vertices[] = {
         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f,  0.5f
    };

    // Indices define how to use vertices to create the square's two triangles.
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Generate and set up a Vertex Array Object, Vertex Buffer Object, and Element Buffer Object.
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO first.
    glBindVertexArray(VAO);

    // Bind and set vertex buffer(s).
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set element buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure vertex attributes.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind buffers.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create the shader program.
    GLuint shaderProgram = createShaderProgram();

    // Main loop: Continue until the window is closed.
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader program.
        glUseProgram(shaderProgram);
        // Bind the VAO.
        glBindVertexArray(VAO);
        // Draw the square using element buffer (indices).
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap the screen buffers.
        glfwSwapBuffers(window);
        // Check for any events, like a key press or mouse movement.
        glfwPollEvents();
    }

    // Clean up.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW.
    glfwTerminate();
    return 0;
}
