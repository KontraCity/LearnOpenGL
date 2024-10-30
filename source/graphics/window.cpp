#include "graphics/window.hpp"

namespace kc {

void Graphics::Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Window* root = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    root->m_width = width;
    root->m_height = height;
    glViewport(0, 0, width, height);
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
    /* Window specific */
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    /* Camera movement mode */
    Camera::MovementMode movementMode = Camera::MovementMode::Normal;
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        movementMode = Camera::MovementMode::Fast;
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        movementMode = Camera::MovementMode::Slow;

    /* Camera control */
    if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::ZoomReset, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Up, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Down, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Forward, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Backward, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Left, movementMode, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.keyPressed(Camera::Key::Right, movementMode, m_deltaTime);

    /* Texture mix */
    constexpr float MixSpeed = 0.05f, MinMix = 0.0f, MaxMix = 1.0f;
    if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
        m_textureMix = Utility::Limit(m_textureMix + MixSpeed, MinMix, MaxMix);
    if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
        m_textureMix = Utility::Limit(m_textureMix - MixSpeed, MinMix, MaxMix);
}

Graphics::Window::Window(unsigned int width, unsigned int height, const std::string& resourcesDirectoryPath)
    : m_window(nullptr)
    , m_width(static_cast<int>(width))
    , m_height(static_cast<int>(height))
    , m_deltaTime(0.0f)
    , m_lastFrameTime(0.0f)
    , m_textureMix(0.0f)
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
    glfwSetCursorPosCallback(m_window, &Window::CursorPositionCallback);
    glfwSetScrollCallback(m_window, &Window::ScrollCallback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    try
    {
        Stopwatch stopwatch;
        m_shaderProgram.make(resourcesDirectoryPath + "/shaders/shader.vert", resourcesDirectoryPath + "/shaders/shader.frag");
        fmt::print("Shader program built [{} ms]\n", stopwatch.milliseconds());

        stopwatch.reset();
        m_containerTexture.load(resourcesDirectoryPath + "/textures/container.jpg");
        m_awesomeFaceTexture.load(resourcesDirectoryPath + "/textures/awesomeface.png", GL_RGBA, true);
        fmt::print("Textures loaded [{} ms]\n", stopwatch.milliseconds());
    }
    catch (...)
    {
        glfwTerminate();
        throw;
    }

    m_shaderProgram.use();
    m_shaderProgram.set("ContainerTexture", 0);
    m_shaderProgram.set("AwesomeFaceTexture", 1);

    glActiveTexture(GL_TEXTURE0);
    m_containerTexture.bind();
    glActiveTexture(GL_TEXTURE1);
    m_awesomeFaceTexture.bind();
}

Graphics::Window::~Window()
{
    glfwTerminate();
}

void Graphics::Window::run()
{
    constexpr float Vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

    while (!glfwWindowShouldClose(m_window))
    {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        m_deltaTime = currentFrameTime - m_lastFrameTime;
        m_lastFrameTime = currentFrameTime;

        processInput();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_shaderProgram.set("TextureMix", m_textureMix);

        glm::mat4 model(1.0f);
        model = glm::rotate(model, currentFrameTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        m_shaderProgram.set("Model", model);
        m_camera.capture(m_shaderProgram, m_width, m_height);

        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

} // namespace kc
