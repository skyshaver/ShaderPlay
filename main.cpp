#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "julia_data.h"
using namespace julia;

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

// variables to hide mouse when program is first launched
double prevXpos = 0.0;
double prevYpos = 0.0;
bool firstMouseMove = true;
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouseMove)
	{
		prevXpos = xpos;
		prevYpos = ypos;
		firstMouseMove = false;
	}
	
	if (prevXpos != xpos || prevYpos != ypos)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}
// store previous window size
int wXPos, wYPos, wW, wH;
static bool fullscreen = false;
// temp setup glfw keycallback to use esc for exit
void processInput(GLFWwindow* window)
{
	// esc to exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }

	// toggle full screen
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !fullscreen)
	{
		// capture state of window
		glfwGetWindowPos(window, &wXPos, &wYPos);
		glfwGetWindowSize(window, &wW, &wH);
		// switch to exclusive fullscreen
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
		fullscreen = true;
	}
			
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && fullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		// switch back to previous window state
		glfwSetWindowMonitor(window, nullptr, wXPos, wYPos, wW, wH, 0);
		fullscreen = false;
	}

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

	GLFWwindow* window = glfwCreateWindow(WWIDTH, WHEIGHT, "Shader Play", nullptr, nullptr);

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

	// this is the super cool one
	Shader simpleShader("shaders/simple_shader.vert", "shaders/drawing_shader_02.frag");

	// julia shader
	Shader juliaShader("shaders/simple_shader.vert", "shaders/julia.frag");

	// hide mouse cursor on load
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// variables for passing to uniforms
	double mouseXpos, mouseYpos;
	int currentWw, currentWh;

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// shader and uniforms
		// simpleShader.use();

		// julia
		juliaShader.use();

		// time
		static float startTime = glfwGetTime();
		float u_time = glfwGetTime() - startTime;

		// animation
		bias[0] = center[0] + amplitude[0] * sin(.05f * PI * (u_time + phase[0]));
		bias[1] = center[1] + amplitude[1] * sin(.05f * PI * (u_time + phase[1]));


		// julia uniforms
		juliaShader.setInt("maxiter", res);
		juliaShader.setFloat("radius", radius);
		juliaShader.setFloat("zoom", zoom);
		juliaShader.setInt("order", order);
		juliaShader.setVec4("converge", glm::vec4(cc[0], cc[1], cc[2], cc[3]));
		juliaShader.setVec4("diverge", glm::vec4(dc[0], dc[1], dc[2], dc[3]));
		juliaShader.setVec2("bias", glm::vec2(bias[0], bias[1]));
		juliaShader.setVec2("offset", glm::vec2(px, py));
		
		
		//// pass elapsed time uniform
		//static float startTime = glfwGetTime();
		//float u_time = glfwGetTime() - startTime;
		////std::cout << std::abs(sin(u_time)) << '\n';
		//simpleShader.setFloat("u_time", u_time);

		//// screen position uniform
		//glfwGetWindowSize(window, &currentWw, &currentWh);
		//glm::vec2 u_resolution = { float(currentWw), float(currentWh) };
		//simpleShader.setVec2("u_resolution", u_resolution);

		//// pass mouse position uniform
		//glfwGetCursorPos(window, &mouseXpos, &mouseYpos);
		//glm::vec2 u_mousePos = { mouseXpos, mouseYpos };
		//simpleShader.setVec2("u_mousePos", u_mousePos);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//---------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}