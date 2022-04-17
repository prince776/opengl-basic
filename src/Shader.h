#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string vertexSource, fragmentSource;
};

class Shader
{
private:
	std::string filepath;
	unsigned int rendererID;
	std::unordered_map<std::string, int> uniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

	void bind() const;
	void unBind() const;

	void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string &name, int value);
	void setUniformMat4f(const std::string &name, const glm::mat4& matrix);

private:
	int getUniformLocation(const std::string& name);

	unsigned int compileShader(unsigned int type, const std::string &source);
	unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
	ShaderProgramSource parseShader(const std::string &filePath);
};
