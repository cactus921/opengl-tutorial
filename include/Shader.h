#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader
{
    
    private:
        void Release(); 
        std::string m_FilePath;
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

        unsigned int GetUniformLocation(const std::string& name);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        ShaderProgramSource ParseShader(const std::string& filepath);


    public:
        Shader(const std::string& filepath);
        //virtual ~Shader();

        ~Shader() {Release();};
        Shader(const Shader&) = delete;
        Shader &operator=(const Shader&) = delete;
        Shader(Shader &&other)  :   m_RendererID(other.m_RendererID)
        {
            other.m_RendererID = 0;
        }
        Shader &operator=(Shader &&other)
        {
            if(this != &other)
            {
                Release();
                m_RendererID = other.m_RendererID;
                other.m_RendererID = 0;
                m_UniformLocationCache = other.m_UniformLocationCache;
            }
            return *this;
        }
        
        void Bind() const;
        void Unbind() const;

        //Set uniforms
        void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1u(const std::string& name, uint value);

    protected:

};

#endif // SHADER_H
