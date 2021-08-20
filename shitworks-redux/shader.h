#pragma once
#include <glm/glm.hpp>

class Shader
{
private:
	// Program ID
	unsigned int ID;
public:
	Shader();
	Shader(const char* vertexPath, const char* fragPath);
	// TODO: Destructor

	void activate();

	void setBool(const char* name, bool value) const;
	void setInt(const char* name, int value) const;
	void setFloat(const char* name, float value) const;
	void setMat4(const char* name, const glm::mat4& matrix) const;
};