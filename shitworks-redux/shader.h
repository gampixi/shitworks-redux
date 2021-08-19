#pragma once

class Shader
{
private:
	// Program ID
	unsigned int ID;
public:
	Shader(const char* vertexPath, const char* fragPath);
	// TODO: Destructor

	void activate();

	void setBool(const char* name, bool value) const;
	void setInt(const char* name, int value) const;
	void setFloat(const char* name, float value) const;
};