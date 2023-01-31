#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

//TRIFORCE VERTICES

//GLfloat vertices[] =
//{	//				COORDINATES							//	COLORS
//	-0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f,	0.3f,	0.02f,		// bottom left
//	0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f,	0.3f,	0.02f,		// bottom right
//	0.0f,		0.5f * float(sqrt(3)) * 2 / 3,	0.0f,	1.0f,	0.6f,	0.32f,		// top
//	-0.5f / 2,	0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f,	0.45f,	0.17f,		// mid left
//	0.5f / 2,	0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f,	0.45f,	0.17f,		// mid right
//	0.0f,		-0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f,	0.3f,	0.02f		// mid bottom
//};

//GLuint indices[] =
//{
//	0, 3, 5,
//	5, 1, 4,
//	3, 4, 2
//};

GLfloat vertices[] =
{	//	VERTEX COORDINATES			//	COLORS				//	TEXTURE COORDINATES
	-0.5f,		0.0f,		0.5f,	0.83f,	0.7f,	0.44f,	0.0f,	0.0f,	// bot left
	-0.5f,		0.0f,		-0.5f,	0.83f,	0.7f,	0.44f,	5.0f,	0.0f,	// top left
	0.5f,		0.0f,		-0.5f,	0.83f,	0.7f,	0.44f,	0.0f,	0.0f,	// top right
	0.5f,		0.0f,		0.5f,	0.83f,	0.7f,	0.44f,	5.0f,	0.0f,	// bot right
	0.0f,		0.8f,		0.0f,	0.92f,	0.86f,	0.76f,	2.5f,	5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW the OpenGL version in use (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a 800 x 800 pixels window named "OpenGLtutorial"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLtutorial", NULL, NULL);

	// Check if the window fails to create. If so, the program is exited
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD
	gladLoadGL();

	// Specify viewport of OpenGL. In this case, it is from (0, 0) to (800, 800)
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0uni, 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	// Keeping the window open until it is told to close
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		// Counter logic
		double counter = glfwGetTime();
		if (counter - prevTime >= (double) 1 / 60) 
		{
			rotation += 0.5;
			prevTime = counter;
		}


		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float) width / height, 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Keeping the window active and responsive to GLFW events
		glfwPollEvents();
	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();

	// Delete window before ending program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}