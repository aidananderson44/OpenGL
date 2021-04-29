#pragma once
#include<string>
#include<unordered_map>
#include "glm/glm.hpp"
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string, int> uniformLocationCache;

public:
	Shader(const std::string& filename);
	Shader(const Shader& other);
	~Shader();

	void Bind() const;
	void UnBind() const;
	void SetMVP(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;
	void SetUniform1i(const std::string& name, int v0) const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat) const;
private:
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name) const;
};

