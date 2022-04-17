#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
	: filepath(filepath), rendererID(0)
{
	auto [vertexSource, fragmentSource] = parseShader(filepath);
	rendererID = createShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(rendererID);
}

void Shader::bind() const
{
	GLCALL(glUseProgram(rendererID));
}

void Shader::unBind() const
{
	GLCALL(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string &name, const glm::mat4& matrix)
{
	GLCALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniform1i(const std::string& name, int value)
{
	GLCALL(glUniform1i(getUniformLocation(name), value));
}

int Shader::getUniformLocation(const std::string &name)
{
	if (uniformLocationCache.count(name))
	{
		return uniformLocationCache[name];
	}
	GLCALL(int location = glGetUniformLocation(rendererID, name.c_str()));
	if (location == -1)
	{
		std::cout << "[Warning]: " << "Uniform '" << name << "' doesn't exist\n";
	}
	uniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::parseShader(const std::string &filePath)
{
	std::ifstream stream(filePath);

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
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
	auto program = glCreateProgram();
	auto vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	auto fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "[" << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << "]:";
		std::cout << "Failed to compile!\n";
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
