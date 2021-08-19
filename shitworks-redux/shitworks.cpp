#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "swlog.h"
#include "renderable.h"
#include "shader.h"
#include "texture.h"
#include "stb_image.h"

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
void sw_render(GLFWwindow* window) {
	glClearColor(1.0f, 0.5255f, 0.0784f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	cabbage->activate(0);
	gopnik->activate(1);

	shader->activate();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);
	shader->setFloat("fader", (sin(glfwGetTime() * 10) * 0.5f) + 0.5f);

	for (auto& r : renderables) {
		glBindVertexArray(r.getVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

	renderables.push_back(Renderable(
		{
	// positions		// colors			// tex coords
	-0.1f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	1.0f, 1.0f,    // top right
	-0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	1.0f, 0.0f,    // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,	0.0f, 1.0f     // top left 
		},
		{
	0, 1, 3, // First triangle
	1, 2, 3 // Second triangle
		}
	));

	renderables.push_back(Renderable(
		{
	// positions		// colors			// tex coords
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	2.0f, 2.0f,  // top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	2.0f, 0.0f,  // bottom right
	 0.1f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
	 0.1f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,	0.0f, 2.0f   // top left 
		},
		{
	0, 1, 3, // First triangle
	1, 2, 3 // Second triangle
		}
	));

	shader = new Shader("default.vertex", "default.fragment");
	cabbage = new Texture("cabbage_lady.png");
	gopnik = new Texture("gopnik.jpg");

	SWLOG("Starting main loop!");
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