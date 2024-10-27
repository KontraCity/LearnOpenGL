#include "shaders/master.hpp"
#include "shaders/shaders.hpp"

namespace kc {

const char* Shaders::Master::ShaderTypeToName(int type)
{
    switch (type)
    {
        case GL_VERTEX_SHADER:
            return "vertex";
        case GL_FRAGMENT_SHADER:
            return "fragment";
        default:
            return "unknown";
    }
}

std::string Shaders::Master::ApplyShaderColor(const char* source, const Color& color)
{
    return fmt::format(
        source,
        color.red / 255.0,
        color.green / 255.0,
        color.blue / 255.0,
        color.opacity / 255.0
    );
}

unsigned int Shaders::Master::CompileShader(const char* source, int type)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int result = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result)
        return shader;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
    std::string error(result, '\0');
    glGetShaderInfoLog(shader, result, nullptr, error.data());
    throw std::runtime_error(fmt::format(
        "kc::Shaders::Master::CompileShader(): Couldn't compile {} shader: \"{}\"",
        ShaderTypeToName(type), error
    ));
}

unsigned int Shaders::Master::LinkShaderProgram(const std::vector<unsigned int>& shaders)
{
    unsigned int program = glCreateProgram();
    for (int shader : shaders)
        glAttachShader(program, shader);
    glLinkProgram(program);

    int result = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result)
        return program;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &result);
    std::string error(result, '\0');
    glGetProgramInfoLog(program, result, nullptr, error.data());
    throw std::runtime_error(fmt::format(
        "kc::Shaders::Master::LinkShaderProgram(): Couldn't link shader program: \"{}\"",
        error
    ));
}

Shaders::Master::Master()
    : m_vertexShader(0)
    , m_fragmentShader(0)
    , m_shaderProgram(0)
{}

Shaders::Master::~Master()
{
    free();
}

void Shaders::Master::compile(const Color& color)
{
    free();
    m_vertexShader = CompileShader(Sources::Vertex, GL_VERTEX_SHADER);
    m_fragmentShader = CompileShader(ApplyShaderColor(Sources::Fragment, color).c_str(), GL_FRAGMENT_SHADER);
    m_shaderProgram = LinkShaderProgram({ m_vertexShader, m_fragmentShader });
    free(false);
}

void Shaders::Master::free(bool freeProgram)
{
    if (m_vertexShader)
    {
        glDeleteShader(m_vertexShader);
        m_vertexShader = 0;
    }

    if (m_fragmentShader)
    {
        glDeleteShader(m_fragmentShader);
        m_fragmentShader = 0;
    }

    if (freeProgram && m_shaderProgram)
    {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
}

} // namespace kc
