#include <glad/glad.h>
#include "stb_image.h"
#include "texture.h"
#include "swlog.h"

Texture::Texture(const char* fileName)
{
	ID = 0;
	SWLOG("Creating texture ", fileName);
	stbi_set_flip_vertically_on_load(true);
	auto imgData = stbi_load(fileName, &width, &height, &channels, 0);
	if (imgData) {
		SWLOG("Loaded texture ", width, "x", height, " channels: ", channels);
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		SWLOG("Failed to load ", fileName, " :( (", stbi_failure_reason(), ")");
	}
	stbi_image_free(imgData);
}

void Texture::activate(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}
