#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include <iostream>

const int WWIDTH = 1280;
const int WHEIGHT = 960;

// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

}

// temp setup glfw keycallback to use esc for exit
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "Couldn't init GLFW!\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WWIDTH, WHEIGHT, "hello", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		return -1;
	}

	// vertices for rectangle, texture mapping inverted but image is mirrored?
	float vertices[] = {
		// positions          // colors           // texture coords
		 1.f,  1.f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // top right
		 1.f, -1.f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // bottom right
		//-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-1.f,  1.f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // top left 

		 1.f, -1.f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // bottom right
		-1.f, -1.f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // bottom left
		-1.f,  1.f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // top left 
		 //0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	};

	// texture buffer setup
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader simpleShader("shaders/simple_shader.vert", "shaders/color_shader_01.frag");

	glm::vec2 u_resolution = { float(WWIDTH), float(WHEIGHT) };

	double mouseXpos, mouseYpos;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// shader and uniforms
		simpleShader.use();
		simpleShader.setVec2("u_resolution", u_resolution);

		// pass elapsed time uniform
		static float startTime = glfwGetTime();
		float u_time = glfwGetTime() - startTime;
		//std::cout << std::abs(sin(u_time)) << '\n';
		simpleShader.setFloat("u_time", u_time);

		// pass mouse position uniform
		glfwGetCursorPos(window, &mouseXpos, &mouseYpos);
		glm::vec2 u_mousePos = { mouseXpos, mouseYpos };
		simpleShader.setVec2("u_mousePos", u_mousePos);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		//---------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}