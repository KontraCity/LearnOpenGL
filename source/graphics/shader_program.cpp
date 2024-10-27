#include "graphics/shader_program.hpp"

namespace kc {

std::string Graphics::ShaderProgram::ReadFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file)
        throw std::runtime_error(fmt::format("kc::Graphics::ShaderProgram::ReadFile(): Couldn't open file \"{}\"", filePath));

    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

const char* Graphics::ShaderProgram::ShaderTypeToName(int type)
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

unsigned int Graphics::ShaderProgram::CompileShader(const char* source, int type)
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
        "kc::Graphics::ShaderProgram::CompileShader(): Couldn't compile {} shader: \"{}\"",
        ShaderTypeToName(type), error
    ));
}

unsigned int Graphics::ShaderProgram::LinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int result = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result)
        return program;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &result);
    std::string error(result, '\0');
    glGetProgramInfoLog(program, result, nullptr, error.data());
    throw std::runtime_error(fmt::format(
        "kc::Graphics::ShaderProgram::LinkShaderProgram(): Couldn't link shader program: \"{}\"",
        error
    ));
}

void Graphics::ShaderProgram::free(bool freeProgram)
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

Graphics::ShaderProgram::ShaderProgram()
    : m_vertexShader(0)
    , m_fragmentShader(0)
    , m_shaderProgram(0)
{}

Graphics::ShaderProgram::~ShaderProgram()
{
    free();
}

void Graphics::ShaderProgram::make(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    free(); // avoid memory leaks if make() is called multiple times
    m_vertexShader = CompileShader(ReadFile(vertexShaderFilePath).c_str(), GL_VERTEX_SHADER);
    m_fragmentShader = CompileShader(ReadFile(fragmentShaderFilePath).c_str(), GL_FRAGMENT_SHADER);
    m_shaderProgram = LinkShaderProgram(m_vertexShader, m_fragmentShader);
    free(false);
}

} // namespace kc
