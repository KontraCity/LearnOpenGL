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
    free(); // avoid memory leaks if make() was called already
    m_vertexShader = CompileShader(ReadFile(vertexShaderFilePath).c_str(), GL_VERTEX_SHADER);
    m_fragmentShader = CompileShader(ReadFile(fragmentShaderFilePath).c_str(), GL_FRAGMENT_SHADER);
    m_shaderProgram = LinkShaderProgram(m_vertexShader, m_fragmentShader);
    free(false);
}

void Graphics::ShaderProgram::use() const
{
    glUseProgram(m_shaderProgram);
}

void Graphics::ShaderProgram::set(const std::string& name, bool boolean)
{
    use();
    int location = glGetUniformLocation(m_shaderProgram, ('u' + name).c_str());
    glUniform1i(location, static_cast<int>(boolean));
}

void Graphics::ShaderProgram::set(const std::string& name, int integer)
{
    use();
    int location = glGetUniformLocation(m_shaderProgram, ('u' + name).c_str());
    glUniform1i(location, integer);
}

void Graphics::ShaderProgram::set(const std::string& name, float real)
{
    use();
    int location = glGetUniformLocation(m_shaderProgram, ('u' + name).c_str());
    glUniform1f(location, real);
}

void Graphics::ShaderProgram::set(const std::string& name, const glm::vec3& vector)
{
    use();
    int location = glGetUniformLocation(m_shaderProgram, ('u' + name).c_str());
    glUniform3fv(location, 1, glm::value_ptr(vector));
}

void Graphics::ShaderProgram::set(const std::string& name, const glm::mat4& matrix)
{
    use();
    int location = glGetUniformLocation(m_shaderProgram, ('u' + name).c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Graphics::ShaderProgram::set(const std::string& name, Color color)
{
    set(name, glm::vec3(color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f));
}

void Graphics::ShaderProgram::set(const std::string& name, const LightProperties& lightProperties)
{
    // Properties
    set(name + ".innerCutoff", glm::cos(glm::radians(lightProperties.innerCutoff)));
    set(name + ".outerCutoff", glm::cos(glm::radians(lightProperties.outerCutoff)));
    set(name + ".ambient", lightProperties.ambient);
    set(name + ".diffuse", lightProperties.diffuse);
    set(name + ".specular", lightProperties.specular);

    // Attenuation
    set(name + ".attenuation.constant", lightProperties.attenuation.constant);
    set(name + ".attenuation.linear", lightProperties.attenuation.linear);
    set(name + ".attenuation.quadratic", lightProperties.attenuation.quadratic);
}

void Graphics::ShaderProgram::set(const std::string& name, const Material& material)
{
    set(name + ".diffuse", material.diffuse, 0);
    set(name + ".specular", material.specular, 1);
    set(name + ".shininess", material.shininess);
}

void Graphics::ShaderProgram::set(const std::string& name, const Texture& texture, int id)
{
    glActiveTexture(GL_TEXTURE0 + id);
    texture.bind();
    set(name, id);
}

} // namespace kc
