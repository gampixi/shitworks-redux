#include "shader.h"
#include "swlog.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

using std::string;
using std::ifstream;
using std::stringstream;

Shader::Shader() : Shader("default.vertex", "default.fragment") {
	SWLOG("Initializing default shader");
}

Shader::Shader(const char* vertexPath, const char* fragPath)
{
	SWLOG("Building shader program from ", vertexPath, " + ", fragPath);
	// Load shader source code
	string vertexCode;
	string fragCode;

	ifstream vertexIn;
	ifstream fragIn;

	// Enable exceptions on input streams
	vertexIn.exceptions(ifstream::failbit | ifstream::badbit);
	fragIn.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		// Open the shader files
		vertexIn.open(vertexPath);
		fragIn.open(fragPath);
		stringstream vertexStream, fragStream;

		// Read the files into stringstreams
		vertexStream << vertexIn.rdbuf();
		fragStream << fragIn.rdbuf();

		// Close the files
		vertexIn.close();
		fragIn.close();

		// Convert stream into string
		vertexCode = vertexStream.str();
		fragCode = fragStream.str();
	}
	catch(ifstream::failure e)
	{
		SWLOG("Failure when loading shader source from disk");
	}

	const char* cVertexCode = vertexCode.c_str();
	const char* cFragCode = fragCode.c_str();

	// Compile vertex and fragment shaders

	unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &cVertexCode, NULL);
	glCompileShader(vertexId);

	{
		int success;
		char infoLog[512];
		glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
			SWLOG("Vertex shader compilation failed: \n", infoLog);
		}
	}

	unsigned int fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, &cFragCode, NULL);
	glCompileShader(fragId);

	{
		int success;
		char infoLog[512];
		glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragId, 512, NULL, infoLog);
			SWLOG("Fragment shader compilation failed: \n", infoLog);
		}
	}
	
	// Link the shader program

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexId);
	glAttachShader(this->ID, fragId);
	glLinkProgram(this->ID);

	{
		int success;
		char infoLog[512];
		glGetProgramiv(this->ID, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
			SWLOG("Shader program linking failed: \n", infoLog);
		}
	}

	// Get rid of compiled shaders
	glDeleteShader(vertexId);
	glDeleteShader(fragId);
}

void Shader::activate()
{
	glUseProgram(this->ID);
}

void Shader::setBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::setInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setMat4(const char* name, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
