#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "swlog.h"
#include "renderable.h"
#include "shader.h"
#include "texture.h"
#include "stb_image.h"
#include "transform.h"

void sw_framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void sw_processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

Texture* cabbage;
Texture* gopnik;
Shader* shader;
std::vector<Renderable> renderables;

Transform cameraTransform;
glm::mat4 cameraProjection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 500.0f);

void sw_render(GLFWwindow* window) {
	glClearColor(1.0f, 0.5255f, 0.0784f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cabbage->activate(0);
	gopnik->activate(1);

	// Do weird transform
	// auto model = glm::mat4(1.0f);
	// model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	// model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.2f, 0.3f, 0.6f));
	// model = glm::scale(model, glm::vec3(1.0f));

	// cameraTransform.rotation *= glm::quat(glm::vec3(0, 0, 0.01));

	for (auto& r : renderables) {
		r.transform.position.y = sin(glfwGetTime()) * 2;
		r.transform.position.x = -cos(glfwGetTime()) * 2;
		r.transform.rotation *= glm::quat(glm::vec3(0.01, 0, 0));
		r.shader->activate();
		r.shader->setMat4("projection", cameraProjection);
		r.shader->setMat4("view", cameraTransform.getViewMatrix());
		r.shader->setInt("texture1", 0);
		r.shader->setInt("texture2", 1);
		r.shader->setFloat("fader", (sin(glfwGetTime() * 10) * 0.5f) + 0.5f);
		r.render();
	}
}

int main(int argc, char* argv[]) {
	SWLOG("Welcome to ShItWorks Redux");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Weird compatibility thing that may or may not break stuff
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "ShItWorks Redux", NULL, NULL);
	if (window == nullptr) {
		SWLOG("Window creation failed");
		// FIXME: Failure should throw and the main loop should always clean up
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		SWLOG("GLAD initialization failed");
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, sw_framebufferSizeCallback);
	glEnable(GL_DEPTH_TEST);

	shader = new Shader("default.vertex", "default.fragment");
	cabbage = new Texture("cabbage_lady.png");
	gopnik = new Texture("gopnik.jpg");

	renderables.push_back(Renderable(
		{
			// positions			// colors			// tex coords
			-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,    // top right
			0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,    // top right
			0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,    // top right
			-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,    // top right
			-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,    // top right
			0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,    // top right
			0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,    // top right
			-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,    // top right
		},
		{
	0, 1, 3, 3, 1, 2,
	1, 5, 2, 2, 5, 6,
	5, 4, 6, 6, 4, 7,
	4, 0, 7, 7, 0, 3,
	3, 2, 7, 7, 2, 6,
	4, 5, 0, 0, 5, 1
		},
		shader));

	SWLOG("Starting main loop!");

	cameraTransform.position = glm::vec3(0.0, 0.0, 4.0);

	// Main rendering loop
	while (!glfwWindowShouldClose(window)) {
		// Logic loop
		sw_processInput(window);

		// Rendering loop
		sw_render(window);

		// Off to the next frame
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}