#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const int NUM_POINTS = 100;

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwSetErrorCallback(errorCallback);

    // Create a GLFW window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sine Wave", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    // Define the points for the sine wave
    GLfloat points[NUM_POINTS * 2];  // (x, y) for each point
    for (int i = 0; i < NUM_POINTS; i++) {
        float x = i * 2.0f * M_PI / NUM_POINTS; // Distribute points along the x-axis
        float y = sin(x);
        points[i * 2] = x;
        points[i * 2 + 1] = y;
    }

    // Create and bind a vertex buffer object (VBO)
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Vertex and fragment shader code (you can create separate .glsl files for this)
    const char* vertexShaderSource =
        "#version 330 core\n"
        "in vec2 position;\n"
        "void main() {\n"
        "    gl_Position = vec4(position, 0.0, 1.0);\n"
        "    gl_PointSize = 5.0;\n"
        "}\n";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color\n"
        "}\n";

    // Create and compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program and link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify how vertex data is organized
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the points as a single point primitive
        glDrawArrays(GL_POINTS, 0, NUM_POINTS);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and exit
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();

    return 0;
}
