// Workaround
#ifdef _MSC_VER
#  pragma execution_character_set("utf-8")
#  pragma warning(disable: 4201)
#endif
#include "../../extlibs/include/GL/glew.h"
#include "../../extlibs/include/GLFW/glfw3.h"
#include "../../extlibs/include/glm/glm.hpp"
#include "../../extlibs/include/glm/gtc/matrix_transform.hpp"
#include "../../extlibs/include/glm/gtc/type_ptr.hpp"
#include "Yaof/Yaof.hpp"

glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
bool keys[1024] = {false};
void key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
void do_movement(float deltaTime);

int main(int, char**)
{
    auto const screenWidth = 800;
    auto const screenHeight = 600;

    YAOF_APPLICATION.initialize(screenWidth, screenHeight, "Test - Yaof");
    YAOF_RESOURCEMANAGER.initialize("resources/test-resources.xml");

    glfwSetKeyCallback(const_cast<GLFWwindow *>(&YAOF_APPLICATION.getWindow().getGlfwWindow()), key_callback);
    glEnable(GL_DEPTH_TEST);

    const yf::FileInputStream vertexStream("resources/test-vertex.glsl");
    const yf::FileInputStream fragmentStream("resources/test-fragment.glsl");
    yf::Shader shader(vertexStream, fragmentStream);

    auto const& containerImage = dynamic_cast<yf::Image const&>(YAOF_RESOURCEMANAGER.getResource("ImageContainer"));
    auto const& awesomeFaceImage = dynamic_cast<yf::Image const&>(YAOF_RESOURCEMANAGER.getResource("ImageAwesomeFace"));
    yf::Texture containerTexture(containerImage);
    yf::Texture awesomeFaceTexture(awesomeFaceImage);

    float pyramidVertices[] = {
        -1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, -1.0, 0.0, 1.0, 1.0,
        0.0, 0.0, 1.0, 1.0, 0.0,

        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, -1.0, 0.0, 1.0, 1.0,
        1.0, 0.0, 0.0, 1.0, 0.0,

        1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, -1.0, 0.0, 1.0, 1.0,
        0.0, 0.0, -1.0, 1.0, 0.0,

        0.0, 0.0, -1.0, 0.0, 0.0,
        0.0, -1.0, 0.0, 1.0, 1.0,
        -1.0, 0.0, 0.0, 1.0, 0.0,

        -1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        1.0, 0.0, 0.0, 1.0, 0.0,

        1.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, -1.0, 1.0, 1.0,
        -1.0, 0.0, 0.0, 0.0, 1.0
    };

    glm::vec3 pyramidPositions[] = {
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(2.0, 5.0, -15.0),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0, -7.5f),
        glm::vec3(1.3f, -2.0, -2.5f),
        glm::vec3(1.5f, 2.0, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0, -1.5f)
    };

    //float vertices[] = {
    //	// Positions        // Colors
    //	0.5f, -0.5f, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, // Bottom Right
    //	-0.5f, -0.5f, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, // Bottom Left
    //	0.0, 0.5f, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0 // Top 
    //};

    //GLuint indices[] = {
    //	0, 1, 2
    //};

    GLuint vbo{}, /*ebo{},*/ vao{};
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    //glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    // Color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);

    // TexCoord attribute
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(const_cast<GLFWwindow *>(&YAOF_APPLICATION.getWindow().getGlfwWindow())))
    {
        YAOF_FPSLIMITER.tick();

        glfwPollEvents();
        do_movement(YAOF_FPSLIMITER.getDeltaTime());

        glClearColor(0.9f, 0.9f, 0.9f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTexture.getGlTextureId());
        glUniform1i(glGetUniformLocation(shader.getGlProgramId(), "containerTexture"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeFaceTexture.getGlTextureId());
        glUniform1i(glGetUniformLocation(shader.getGlProgramId(), "awesomeFaceTexture"), 1);

        //glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        //model = glm::rotate(model, -20.0, glm::vec3(1.0, 0.0, 0.0));
        //model = glm::rotate(model, static_cast<GLfloat>(glfwGetTime()) * 1.0, glm::vec3(0.5f, 1.0, 0.0));
        //view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));

        view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        projection = glm::perspective(45.0f, static_cast<GLfloat>(screenWidth) / screenHeight, 0.1f, 100.0f);

        const auto modelLoc = glGetUniformLocation(shader.getGlProgramId(), "model");
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        const auto viewLoc = glGetUniformLocation(shader.getGlProgramId(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

        const auto projectionLoc = glGetUniformLocation(shader.getGlProgramId(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

        glBindVertexArray(vao);

        for (GLuint i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = translate(model, pyramidPositions[i]);
            model = rotate(model, static_cast<GLfloat>(glfwGetTime()) * (i + 1),
                           glm::vec3(0.1f, (i / 2 == 0) ? 1.0 : -1.0, 0.3f));
            model = scale(model, glm::vec3(0.7f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 18);
        }

        //glDrawArrays(GL_TRIANGLES, 0, 18);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(const_cast<GLFWwindow *>(&YAOF_APPLICATION.getWindow().getGlfwWindow()));
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &ebo);

    YAOF_APPLICATION.terminate();

    return 0;
}

void key_callback(GLFWwindow*, const int32_t key, int32_t, const int32_t action, int32_t)
{
    if (action == GLFW_PRESS)
    {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key] = false;
    }
}

void do_movement(const float deltaTime)
{
    const auto cameraSpeed = 6.0f * deltaTime;
    if (keys[GLFW_KEY_W])
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (keys[GLFW_KEY_S])
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (keys[GLFW_KEY_A])
    {
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (keys[GLFW_KEY_D])
    {
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}
