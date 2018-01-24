#include "../../extlibs/include/GL/glew.h"
#include "../../extlibs/include/GLFW/glfw3.h"
#include "Yaof/Yaof.hpp"

int main(int, char**)
{
    yf::Singleton<yf::Application>::getInstance().initialize(800, 600, "HelloTriangle - Yaof");

    const yf::FileInputStream vertexStream("resources/triangle-vertex.glsl");
    const yf::FileInputStream fragmentStream("resources/triangle-fragment.glsl");

    yf::Shader shader(vertexStream, fragmentStream);

    float vertices[] = {
        // Positions       // Colors
        0.5f, -0.5f, 0.0, 1.0, 0.0, 0.0, // Bottom Right
        -0.5f, -0.5f, 0.0, 0.0, 1.0, 0.0, // Bottom Left
        0.0, 0.5f, 0.0, 0.0, 0.0, 1.0 // Top 
    };

    GLuint vbo = 0, vao = 0;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(const_cast<GLFWwindow *>(&YAOF_APPLICATION.getWindow().getGlfwWindow())))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(const_cast<GLFWwindow *>(&YAOF_APPLICATION.getWindow().getGlfwWindow()));
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    YAOF_APPLICATION.terminate();

    return 0;
}
