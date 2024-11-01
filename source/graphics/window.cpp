#include "graphics/window.hpp"

namespace kc {

void Graphics::Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Window* root = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    root->m_width = width;
    root->m_height = height;
    glViewport(0, 0, width, height);
}

void Graphics::Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* root = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
        {
            if (action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
            break;
        }
        case GLFW_KEY_TAB:
        {
            if (action == GLFW_PRESS || action == GLFW_REPEAT)
                root->toggleWireframe();
            break;
        }
        case GLFW_KEY_Q:
        {
            if (action == GLFW_PRESS)
                root->toggleVSync();
            break;
        }
        case GLFW_KEY_E:
        {
            if (action == GLFW_PRESS)
                root->m_lightAnimation = !root->m_lightAnimation;
            break;
        }
        case GLFW_KEY_R:
        {
            if (action == GLFW_PRESS)
                root->m_camera.resetZoom();
            else if (action == GLFW_REPEAT)
                root->m_camera.resetPosition();
            break;
        }
    }
}

void Graphics::Window::CursorPositionCallback(GLFWwindow* window, double x, double y)
{
    static float lastX = x, lastY = y;
    float xOffset = x - lastX, yOffset = lastY - y;
    lastX = x; lastY = y;

    Window* root = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    root->m_camera.mouseMoved(xOffset, yOffset);
}

void Graphics::Window::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    Window* root = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    root->m_camera.mouseScrolled(yOffset);
}

void Graphics::Window::processInput()
{
    /* Camera movement mode */
    Camera::MovementMode movementMode = Camera::MovementMode::Normal;
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        movementMode = Camera::MovementMode::Fast;
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        movementMode = Camera::MovementMode::Slow;

    /* Camera movement */
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Up, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Down, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Forward, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Backward, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Left, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Right, movementMode, m_deltaTime);
}

void Graphics::Window::toggleWireframe()
{
    static bool wireframe = false;
    wireframe = !wireframe;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
}

void Graphics::Window::toggleVSync()
{
    static bool enabled = true;
    enabled = !enabled;
    glfwSwapInterval(static_cast<int>(enabled));
}

void Graphics::Window::showFps()
{
    float fps = 1.0f / m_deltaTime;
    static float min, max, resetTime = -1.0f;
    if (resetTime == -1 || m_currentFrameTime - resetTime > 3.0f)
    {
        min = max = fps;
        resetTime = m_currentFrameTime;
    }

    if (fps < min)
        min = fps;
    if (fps > max)
        max = fps;
    fmt::print("FPS: {:>6.1f} (min/max for 3s: {:>6.1f}, {:6.1f})\r", fps, min, max);
}

Graphics::Window::Window(unsigned int width, unsigned int height, const std::string& resourcesPath)
    : m_logger(Utility::CreateLogger("window"))
    , m_window(nullptr)
    , m_width(static_cast<int>(width))
    , m_height(static_cast<int>(height))
    , m_currentFrameTime(0.0f)
    , m_deltaTime(0.0f)
    , m_lastFrameTime(0.0f)
    , m_lightAnimation(true)
{
    if (glfwInit() != GLFW_TRUE)
        throw std::runtime_error("kc::Graphics::Window::Window(): Couldn't initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, "LearnOpenGL", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("kc::Graphics::Window::Window(): Couldn't create GLFW window");
    }
    glfwMakeContextCurrent(m_window);

    GLenum result = glewInit();
    if (result != GLEW_OK)
    {
        glfwTerminate();
        throw std::runtime_error(fmt::format(
            "kc::Graphics::Window::Window(): Couldn't initialize GLEW: \"{}\"",
            reinterpret_cast<const char*>(glewGetErrorString(result)
        )));
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, m_width, m_height);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, &Window::FrameBufferSizeCallback);
    glfwSetKeyCallback(m_window, &Window::KeyCallback);
    glfwSetCursorPosCallback(m_window, &Window::CursorPositionCallback);
    glfwSetScrollCallback(m_window, &Window::ScrollCallback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    try
    {
        Stopwatch stopwatch;
        m_shaderProgram.make(resourcesPath + "/shaders/cube.vert", resourcesPath + "/shaders/cube.frag");
        m_lightShaderProgram.make(resourcesPath + "/shaders/light.vert", resourcesPath + "/shaders/light.frag");
        m_logger.info("Shader programs built [{} ms]", stopwatch.milliseconds());

        stopwatch.reset();
        m_containerTexture.load(resourcesPath + "/textures/container2.png", GL_RGBA, true);
        m_containerSpecularTexture.load(resourcesPath + "/textures/container2_specular.png", GL_RGBA, true);
        m_logger.info("Textures loaded [{} ms]", stopwatch.milliseconds());
    }
    catch (...)
    {
        glfwTerminate();
        throw;
    }
}

Graphics::Window::~Window()
{
    glfwTerminate();
}

void Graphics::Window::run()
{
    Light light;
    light.transform() = { glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.2f) };
    light.properties() = { 0.2f, 0.5f, 1.0f };

    Cube cube;
    cube.material().diffuse = m_containerTexture;
    cube.material().specular = m_containerSpecularTexture;
    cube.material().shininess = 64.0f;

    while (!glfwWindowShouldClose(m_window))
    {
        m_currentFrameTime = glfwGetTime();
        m_deltaTime = m_currentFrameTime - m_lastFrameTime;
        m_lastFrameTime = m_currentFrameTime;
        showFps();

        processInput();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Transform
        if (m_lightAnimation)
        {
            light.transform().position.x = std::sin(m_currentFrameTime) * 1.5f;
            light.transform().position.z = std::cos(m_currentFrameTime) * 1.5f;
        }
        else
        {
            light.transform().position = glm::vec3(1.5f, 1.0f, 1.5f);
        }

        // Draw
        light.draw(m_shaderProgram, m_lightShaderProgram);
        cube.draw(m_shaderProgram);

        m_camera.capture({ m_shaderProgram, m_lightShaderProgram }, m_width, m_height);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    m_logger.info("{:<20}", "Stopped");
}

} // namespace kc
