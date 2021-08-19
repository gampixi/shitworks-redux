#pragma once
#include <vector>

class Renderable {
private:
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;
	void CreateVBO(std::vector<float>& vertices);
	void CreateEBO(std::vector<unsigned int>& indices);
	void CreateVAO();
public:
	Renderable(std::vector<float> vertices, std::vector<unsigned int> indices);
	// TODO: Destructor
	unsigned int getVAO() { return VAO; }
};