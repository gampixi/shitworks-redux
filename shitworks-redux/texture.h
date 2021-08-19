#pragma once

class Texture {
private:
	unsigned int ID;
	int width;
	int height;
	int channels;
public:
	Texture(const char* fileName);
	void activate(int unit = 0);
};