#include "Shader.h"
#include "Renderer.h"
#include "DebugManager.h"


Shader::Shader(const std::string& filepath)
    : m_FilePath(filepath), m_RendererID(0)
{
    //ctor
    ShaderProgramSource source = ParseShader(filepath);
    GLCALL(m_RendererID = CreateShader(source.VertexSource, source.FragmentSource));
    //GLDebugOut("Shader created, with ID", m_RendererID);
}
/*
Shader::~Shader()
{
    //dtor
    GLCALL(glDeleteProgram(m_RendererID));
}
*/

void Shader::Release()
{
    //dtor
    GLCALL(glDeleteProgram(m_RendererID));
    //GLDebugOut("Shader deleted, with ID", m_RendererID);
    m_RendererID = 0;
}

void Shader::Bind() const
{
    //GLDebugOut("Binding shader, with ID", m_RendererID);
    GLCALL(glUseProgram(m_RendererID));
    //GLDebugOut("Shader bound, with ID", m_RendererID);
}


void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
    //("Shader unbound, with ID", m_RendererID);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
    Bind();
    GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    Bind();
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    Bind();
    GLCALL(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    Bind();
    GLCALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    Bind();
    GLCALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1u(const std::string& name, uint value)
{
    Bind();
    GLCALL(glUniform1ui(GetUniformLocation(name), value));
}


unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;

    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;

            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCALL(unsigned int program = glCreateProgram());
    GLCALL(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
    GLCALL(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}

