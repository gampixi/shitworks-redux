#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderable.h"
#include "swlog.h"

Renderable::Renderable(std::vector<float> vertices, std::vector<unsigned int> indices, Shader* shader) {
	CreateVBO(vertices);
	CreateEBO(indices);
	CreateVAO();
	this->shader = shader;
}

void Renderable::render()
{
	shader->activate();
	shader->setMat4("transform", transform.getWorldMatrix());
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

void Renderable::CreateVBO(std::vector<float>& vertices) {
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
}

void Renderable::CreateEBO(std::vector<unsigned int>& indices) {
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
	numIndices = indices.size();
}

void Renderable::CreateVAO() {
	SWLOG("Building VAO with VBO ", VBO, ", EBO ", EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Enable vertex position array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Enable vertex color array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Enable texture coordinate array
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}