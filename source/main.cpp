// STL modules
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// External modules
#include "external/stb_image.h"

// Custom modules
#include "common/stopwatch.hpp"
#include "common/utility.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"
using namespace kc;

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    fmt::print("{}x{}\n", width, height);
}

static void Run()
{
    if (glfwInit() != GLFW_TRUE)
        throw std::runtime_error("Couldn't initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Couldn't create GLFW window");
    }
    glfwMakeContextCurrent(window);

    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK)
    {
        glfwTerminate();
        throw std::runtime_error(fmt::format(
            "Couldn't initialize GLEW: \"{}\"",
            reinterpret_cast<const char*>(glewGetErrorString(glewResult)
        )));
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    Graphics::ShaderProgram shaderProgram;
    try
    {
        Stopwatch stopwatch;
        shaderProgram.make("../../resources/shaders/shader.vert", "../../resources/shaders/shader.frag");
        fmt::print("Shader program built in {} ms\n", stopwatch.milliseconds());
    }
    catch (...)
    {
        glfwTerminate();
        throw;
    }
    shaderProgram.use();

    Graphics::Texture containerTexture, awesomeFaceTexture;
    try
    {
        Stopwatch stopwatch;
        containerTexture.load("../../resources/textures/container.jpg");
        awesomeFaceTexture.load("../../resources/textures/awesomeface.png", GL_RGBA, true);
        fmt::print("Textures loaded in {} ms\n", stopwatch.milliseconds());
    }
    catch (...)
    {
        glfwTerminate();
        throw;
    }
    shaderProgram.set("ContainerTexture", 0);
    shaderProgram.set("AwesomeFaceTexture", 1);

    constexpr float Vertices[] = {
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
    };

    constexpr int Indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    unsigned int vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    unsigned int elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    float textureMix = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            textureMix += 0.05f;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            textureMix -= 0.05f;
        textureMix = Utility::Limit(textureMix, 0.0f, 1.0f);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderProgram.set("TextureMix", textureMix);
        glActiveTexture(GL_TEXTURE0);
        containerTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        awesomeFaceTexture.bind();

        float time = static_cast<float>(glfwGetTime());
        float scale = (std::sin(time * M_PI) + 1.0f) / 2.0f;
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        transform = glm::scale(transform, glm::vec3(scale * 0.7f, scale * 0.7f, scale * 0.7f));
        shaderProgram.set("Transform", transform);

        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, glm::radians(time * 90.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        transform = glm::scale(transform, glm::vec3(0.7f, 0.7f, 0.7f));
        shaderProgram.set("Transform", transform);

        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

int main()
{
    try
    {
        Run();
        return 0;
    }
    catch (const std::runtime_error& error)
    {
        fmt::print(stderr, "Runtime error: {}\n", error.what());
        return -1;
    }
}
