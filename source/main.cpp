// STL modules
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Custom modules
#include "common/stopwatch.hpp"
#include "graphics/shader_program.hpp"
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
        shaderProgram.make("../../shaders/shader.vert", "../../shaders/shader.frag");
        fmt::print("Shader program made in {} ms\n", stopwatch.milliseconds());
    }
    catch (const std::runtime_error&)
    {
        glfwTerminate();
        throw;
    }
    shaderProgram.use();

    constexpr float Vertices[] = {
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.0f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    };

    unsigned int vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
