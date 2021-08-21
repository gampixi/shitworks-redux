#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "shader.h"
#include "transform.h"

class Renderable {
private:
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;
	unsigned int numIndices;
	void CreateVBO(std::vector<float>& vertices);
	void CreateEBO(std::vector<unsigned int>& indices);
	void CreateVAO();
public:
	Shader* shader;
	Transform transform;
	Renderable(std::vector<float> vertices, std::vector<unsigned int> indices, Shader* shader);
	// TODO: Destructor
	unsigned int getVAO() { return VAO; }
	void render();
};