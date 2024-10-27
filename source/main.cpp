// STL modules
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Custom modules
#include "common/stopwatch.hpp"
#include "shaders/master.hpp"
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

    Shaders::Master leftShaderMaster, rightShaderMaster;
    try
    {
        Stopwatch stopwatch;
        leftShaderMaster.compile({ 255, 0, 0 });
        rightShaderMaster.compile({ 255, 255, 0 });
        fmt::print("Shaders compiled in {} ms\n", stopwatch.milliseconds());
    }
    catch (const std::runtime_error&)
    {
        glfwTerminate();
        throw;
    }

    constexpr float LeftVertices[] = {
        -0.5f - 0.3f, -0.5f, 0.0f,
        0.0f - 0.3f, 0.5f, 0.0f,
        0.5f - 0.3f, -0.5f, 0.0f,
    };

    unsigned int leftVertexArrayObject;
    glGenVertexArrays(1, &leftVertexArrayObject);
    glBindVertexArray(leftVertexArrayObject);

    unsigned int leftVertexBufferObject;
    glGenBuffers(1, &leftVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, leftVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(LeftVertices), LeftVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    constexpr float RightVertices[] = {
        -0.5f + 0.3f, 0.5f, 0.0f,
        0.0f + 0.3f, -0.5f, 0.0f,
        0.5f + 0.3f, 0.5f, 0.0f,
    };

    unsigned int rightVertexArrayObject;
    glGenVertexArrays(1, &rightVertexArrayObject);
    glBindVertexArray(rightVertexArrayObject);

    unsigned int rightVertexBufferObject;
    glGenBuffers(1, &rightVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, rightVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RightVertices), RightVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);
    
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        leftShaderMaster.use();
        glBindVertexArray(leftVertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        rightShaderMaster.use();
        glBindVertexArray(rightVertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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
