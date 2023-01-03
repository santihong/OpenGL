#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utils.h"
#include "Shader.h"
#include "stb_image.h"
using namespace std;

#define STBI_FAILURE_USERMSG

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Check glad init.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Create and bind VAO.
    // VAOs: on VAO contain one VBO, one VBO contains multi vertex attributes.
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // First traiangle.
    // Create and bind VBO.
    float vertices[] = {
         // positions           // color            // texture coords TODO: why texture coords must be -1, otherwise image shows oppsite.
         0.5f,  0.5f, 0.0f,     1.0, 0.0, 0.0,      1.0, 1.0, // top right
         0.5f, -0.5f, 0.0f,     0.0, 1.0, 0.0,      1.0, 0.0, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0, 0.0, 1.0,      0.0, 0.0, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0, 0.0, 1.0,      0.0, 1.0, // top left
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Use EBO instead of VBO, to decrease duplicate vertices.
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex data for shader input.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set vertex color data for shader input.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set texture coords.
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load texture and bind.
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nChannels;
    unsigned char* data = stbi_load("lenna.png", &width, &height, &nChannels, 0);
    if (data)
    {
        cout << "image: " << width << ", " << height << ", " << nChannels << endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }
    stbi_image_free(data);

    // Load and compile shader program.
    Shader shader("triangle.vert", "triangle.frag");
    shader.use();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        shader.setVec4f("tilingColor", 0.0f, greenValue, 0.0f, 1.0f);

        // Draw objects...
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}