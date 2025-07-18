#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

using namespace std;

void OnFrameSizeChanged(GLFWwindow* window, int width, int height)
{
	cout << "OnFrameSizeChanged: " << width << ", " << height << endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* wind)
{
	if (glfwGetKey(wind, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(wind, true);
	}
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* wind = glfwCreateWindow(800, 600, "HelloOpenGL", NULL, NULL);
	if (wind == NULL) {
		cerr << "Failed to create glfw window." << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(wind);

	// glad init.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to init glad." << endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(wind, OnFrameSizeChanged);


	// Configure a triangle.

	// Vertex data.
	float vertices[] = {
		// position		// color	
		0.5, 0.5, 0,	1, 0, 0, 1,
		-0.5, 0.5, 0,	0, 1, 0, 1,
		-0.5, -0.5, 0,	0, 0, 1, 1,
		0.5, -0.5, 0,	1, 1, 1, 1
	};
	
	// vertex index data.
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	// 0. Bind VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 1. Gen VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Gen EBO(Element Buffer Object).
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Set vertex attribute for vs.

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// Unbind VAO.
	glBindVertexArray(0);

	// configure shader.
	Shader HelloShader("hello.vs", "hello.fs");

	while (!glfwWindowShouldClose(wind)) {
		processInput(wind);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	
		HelloShader.use();

		// Set uniform params.
		float cur_time = glfwGetTime();
		float green_value = sin(cur_time) / 2.0 + 0.5f;
		HelloShader.setVec4f("OutColor", 0, green_value, 0, 1.0);

		// Draw
	
		// Draw mode
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(wind);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}
