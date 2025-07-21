#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"

using namespace std;

void OnFrameSizeChanged(GLFWwindow* window, int width, int height)
{
	//cout << "OnFrameSizeChanged: " << width << ", " << height << endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* wind)
{
	if (glfwGetKey(wind, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(wind, true);
	}
}

int init_texture(const char* img_path, GLuint texture)
{
	// Load image
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(img_path, &width, &height, &nChannel, 0);
	if (!data) {
		cerr << "Failed to load texture: " << img_path << endl;
		return -1;
	}
	else {
		cout << "Loaded image: " << img_path << ", " << "width: " << width << ", height : " << height << ", channels : " << nChannel << endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	return 0;
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
		// position				// color		// texture coords
		1.0f, 1.0f, 0.0f,		1, 0, 0,		1.0, 1.0,	
		-1.0f, 1.0f, 0.0f,		0, 1, 0,		0.0, 1.0,
		-1.0f, -1.0f, 0.0f,		0, 0, 1,		0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,		1, 1, 1,		1.0f, 0.0f,
	};
	
	// vertex index data.
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	// Set image wrapper and filter params.
	// wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Gen image textures
	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);
	init_texture("lenna.png", texture1);
	init_texture("rocket.png", texture2);
	
	// Unbind VAO.
	glBindVertexArray(0);

	// configure shader.
	Shader HelloShader("hello.vs", "hello.fs");

	while (!glfwWindowShouldClose(wind)) {
		processInput(wind);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		HelloShader.use();
		
		// tell shader bind texture uniform.
		HelloShader.setInt("texture1", 0);
		HelloShader.setInt("texture2", 1);

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
