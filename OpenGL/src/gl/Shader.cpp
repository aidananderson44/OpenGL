#include "Shader.h"
#include<iostream>
#include <fstream>
#include<string>
#include<sstream>
#include "Renderer.h"
Shader::Shader(const std::string& filename)
	:m_FilePath(filename)
{
    ShaderProgramSource source = ParseShader(filename);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::Shader(const Shader& other):
    m_RendererID(other.m_RendererID),
    m_FilePath(other.m_FilePath),
    uniformLocationCache(other.uniformLocationCache)
{
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const
{
    //TODO scan the vertex shader for appropriate name
    SetUniformMat4f("view", view);
    SetUniformMat4f("model", model);
    SetUniformMat4f("projection", projection);
}

void Shader::SetCameraPosition(const glm::vec3& position) const
{
    SetUniform3f("cameraPosition", position);
}

void Shader::SetUniform1i(const std::string& name, int v0) const
{
    GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& vec) const
{
    GLCall(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist";

    uniformLocationCache[name] = location;
    return location;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int  vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int  fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
    std::fstream stream(filePath);
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
