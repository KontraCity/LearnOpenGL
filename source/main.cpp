// STL modules
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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
