//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "Utils.h"
//#include "Shader.h"
//#include "stb_image.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//using namespace std;
//
//#define STBI_FAILURE_USERMSG
//
//// frame params.
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// camera params.
//const float cameraSpeed = 2.5f; // adjust accordingly
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//// mouse params.
//float lastX = 400, lastY = 300;
//float pitch = 0.0f;
//float yaw = -90.0f;
//const float sensitivity = 0.1f;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//
//bool bFirstMouse = true;
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//    if (bFirstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        bFirstMouse = false;
//    }
//    
//    float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//    
//    yaw += xoffset;
//    pitch += yoffset;
//
//    if(pitch > 89.0f)
//	  pitch =  89.0f;
//	if(pitch < -89.0f)
//	  pitch = -89.0f;
//
//	glm::vec3 direction;
//	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	direction.y = sin(glm::radians(pitch));
//	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//	cameraFront = glm::normalize(direction);
//}
//
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//
//	// process input control camera.
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		cameraPos += cameraSpeed * cameraFront * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cameraPos -= cameraSpeed * cameraFront * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
//}
//
//int bindTextureImage(GLuint texture, const char* imagePath) {
//    // OpenGL (0, 0) is bottom-left, image file read by library (0, 0) is top-left. So here need to flip y.
//    stbi_set_flip_vertically_on_load(true);
//    
//    int width, height, nChannels;
//    glBindTexture(GL_TEXTURE_2D, texture);
//    // set the texture wrapping/filtering options (on the currently bound texture object)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    unsigned char* data = stbi_load(imagePath, &width, &height, &nChannels, 0);
//    if (data)
//    {
//        cout << imagePath << ": " << width << ", " << height << ", " << nChannels << endl;
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture: " << imagePath << std::endl;
//        return -1;
//    }
//    stbi_image_free(data);
//
//    return 0;
//}
//
//int main() {
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    // Check glad init.
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glViewport(0, 0, 800, 600);
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
//    glfwSetCursorPosCallback(window, mouse_callback);
//
//    // Create and bind VAO.
//    // VAOs: on VAO contain one VBO, one VBO contains multi vertex attributes.
//    GLuint VAO;
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//    
//    // First traiangle.
//    // Create and bind VBO.
//    // TODO texture coords not correct.
//    float vertices[] = {
//         // positions           // color                // texture coords   // normals  
//        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,       0.0f, 0.0f,         0.0f,  0.0f, -1.0f, 
//         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 		1.0f, 0.0f,         0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,		1.0f, 1.0f,      	0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,		1.0f, 1.0f,      	0.0f,  0.0f, -1.0f,
//        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,		0.0f, 1.0f,      	0.0f,  0.0f, -1.0f,
//        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,		0.0f, 0.0f,      	0.0f,  0.0f, -1.0f,
//							                                             	
//        -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,		0.0f, 0.0f,      	0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,		1.0f, 0.0f,      	0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,		1.0f, 1.0f,      	0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,		1.0f, 1.0f,      	0.0f,  0.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,		0.0f, 1.0f,      	0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,		0.0f, 0.0f,      	0.0f,  0.0f, 1.0f,
//							                                             	
//        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,      	-1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,		1.0f, 1.0f,      	-1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,      	-1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,		0.0f, 1.0f,      	-1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f,      	-1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,		1.0f, 0.0f,      	-1.0f,  0.0f,  0.0f,
//							                                             	
//         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,      	1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,		1.0f, 1.0f,      	1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,      	1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,		0.0f, 1.0f,      	1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f,      	1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,		1.0f, 0.0f,      	1.0f,  0.0f,  0.0f,
//							                                             	
//        -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,		0.0f, 1.0f,      	0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,		1.0f, 1.0f,      	0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,		1.0f, 0.0f,      	0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,      	0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f,      	0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,      	0.0f, -1.0f,  0.0f,
//							                                             	
//        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,		0.0f, 1.0f,      	0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,		1.0f, 1.0f,      	0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,		1.0f, 0.0f,      	0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,      	0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f,      	0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,       	0.0f,  1.0f,  0.0f
//    };
//    
//    glm::vec3 cubePositions[] = {
//        glm::vec3(0.0f,  0.0f,  0.0f),
//        glm::vec3(2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3(1.3f, -2.0f, -2.5f),
//        glm::vec3(1.5f,  2.0f, -2.5f),
//        glm::vec3(1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    // positions of the point lights
//    glm::vec3 pointLightPositions[] = {
//        glm::vec3( 0.7f,  0.2f,  2.0f),
//        glm::vec3( 2.3f, -3.3f, -4.0f),
//        glm::vec3(-4.0f,  2.0f, -12.0f),
//        glm::vec3( 0.0f,  0.0f, -3.0f)
//    };
//
//    GLuint VBO;
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // Set vertex data for shader input.
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Set vertex color data for shader input.
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // Set texture coords.
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    // Set normals.
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
//    glEnableVertexAttribArray(3);
//
//    // Load texture and bind.
//    unsigned int textures[2];
//    glGenTextures(2, textures);
//    
//    bindTextureImage(textures[0], "box_diffuse.png");
//    bindTextureImage(textures[1], "box_spec.png");
//
//    // Load and compile shader program.
//    Shader shader("triangle.vert", "triangle.frag");
// 
//    // Lamp model
//	unsigned int lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	// we only need to bind to the VBO, the container's VBO's data already contains the data.
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// set the vertex attribute 
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//    // Light shader
//    Shader lightShader("light.vert", "light.frag");
//    
//    while (!glfwWindowShouldClose(window)) {
//		// process input.
//        processInput(window);
//      
//        float curFrame = glfwGetTime();
//        if (lastFrame > 0.0f) {
//            deltaTime = curFrame - lastFrame;
//        }
//        lastFrame = curFrame;
//
//        glEnable(GL_DEPTH_TEST);
//        glClearColor(0, 0, 0, 1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//      
//        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//		shader.use(); // Must activate before set uniforms!
//        shader.setVec3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
//        /*
//           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index 
//           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
//           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
//           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
//        */
//        // directional light
//        shader.setVec3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        shader.setVec3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//        shader.setVec3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//        shader.setVec3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
//        // point light 1
//        shader.setVec3f("pointLights[0].position", pointLightPositions[0]);
//        shader.setVec3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//        shader.setVec3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//        shader.setVec3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//        shader.setFloat("pointLights[0].constant", 1.0f);
//        shader.setFloat("pointLights[0].linear", 0.09f);
//        shader.setFloat("pointLights[0].quadratic", 0.032f);
//        // point light 2
//        shader.setVec3f("pointLights[1].position", pointLightPositions[1]);
//        shader.setVec3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//        shader.setVec3f("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//        shader.setVec3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//        shader.setFloat("pointLights[1].constant", 1.0f);
//        shader.setFloat("pointLights[1].linear", 0.09f);
//        shader.setFloat("pointLights[1].quadratic", 0.032f);
//        // point light 3
//        shader.setVec3f("pointLights[2].position", pointLightPositions[2]);
//        shader.setVec3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//        shader.setVec3f("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//        shader.setVec3f("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//        shader.setFloat("pointLights[2].constant", 1.0f);
//        shader.setFloat("pointLights[2].linear", 0.09f);
//        shader.setFloat("pointLights[2].quadratic", 0.032f);
//        // point light 4
//        shader.setVec3f("pointLights[3].position", pointLightPositions[3]);
//        shader.setVec3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//        shader.setVec3f("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//        shader.setVec3f("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//        shader.setFloat("pointLights[3].constant", 1.0f);
//        shader.setFloat("pointLights[3].linear", 0.09f);
//        shader.setFloat("pointLights[3].quadratic", 0.032f);
//        // spotLight
//        shader.setVec3f("spotLight.position", cameraPos);
//        shader.setVec3f("spotLight.direction", cameraFront);
//        shader.setVec3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//        shader.setVec3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//        shader.setVec3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
//        shader.setFloat("spotLight.constant", 1.0f);
//        shader.setFloat("spotLight.linear", 0.09f);
//        shader.setFloat("spotLight.quadratic", 0.032f);
//        shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//        shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));   
//
//		// Bind texture sampler.
//		shader.setInt("material.diffuse", 0);
//		shader.setInt("material.specular", 1);
//        shader.setFloat("material.shininess", 64);
//
//        // view matrix.
//		const float radius = 10.0f;
//		float camX = sin(glfwGetTime()) * radius;
//		float camZ = cos(glfwGetTime()) * radius;
//		glm::mat4 view;
//		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);  
//        shader.setMatrix4fv("view", glm::value_ptr(view));
//
//        // projection matrix.
//        glm::mat4 projection;
//        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//        shader.setMatrix4fv("projection", glm::value_ptr(projection));
//
//        // Draw objects...
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, textures[0]);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, textures[1]);
//
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * (i + 1);
//            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            shader.setMatrix4fv("model", glm::value_ptr(model));
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//        glBindVertexArray(0);
//
//        // Draw lamp model.
//		glm::mat4 lightModel = glm::mat4(1.0f);
//		lightModel = glm::translate(lightModel, lightPos);
//		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
//        
//        lightShader.use();
//        lightShader.setMatrix4fv("model", glm::value_ptr(lightModel));
//        lightShader.setMatrix4fv("projection", glm::value_ptr(projection));
//        lightShader.setMatrix4fv("view", glm::value_ptr(view));
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//
//    return 0;
//}
