#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "hand.h"
#include "GameObject.h"

using tigl::Vertex;


#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

void OpenGLInit();

void Update();
void Draw();

int width = 700;
int height = 700;

std::vector<GameObject> gameObjects = std::vector<GameObject>();

GLFWwindow* window;

int main()
{
	bool isHand = true;
	if (isHand)
	{
		hand();
	}
	else
	{
		if (!glfwInit())
			throw "Could not initialize glwf";

		//Get primary monitor size so that the fullscreen application can have the correct resolution
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		glfwGetMonitorWorkarea(monitor, nullptr, nullptr, &width, &height);

		window = glfwCreateWindow(width, height, "A1 Augmented Reality", monitor, nullptr);

		//Check if the window was successfully made
		if (!window)
		{
			glfwTerminate();
			throw "Could not initialize glwf";
		}
		glfwMakeContextCurrent(window);

		//Escape key callback to quit application
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				if (key == GLFW_KEY_ESCAPE)
					glfwSetWindowShouldClose(window, true);
			});

		//Init
		OpenGLInit();

		//Test object
		gameObjects.push_back(GameObject("C:/Users/larsv/Desktop/gpu/rtx4090.obj"));

		//MAIN LOOP
		while (!glfwWindowShouldClose(window))
		{
			//program cycle
			Update();
			Draw();

			//glfw cycle
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		//Termination
		glfwDestroyWindow(window);
		glfwTerminate();
		return 0;
	}
}

void OpenGLInit()
{
	tigl::init();

	//First time shaders
	tigl::shader->setProjectionMatrix(glm::perspective(
		glm::radians(90.f),
		(float)width / height,
		0.1f,
		100.f
	));



	tigl::shader->setViewMatrix(glm::lookAt(
		glm::vec3(0, 10, 10),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	));

	tigl::shader->enableColor(true);
	tigl::shader->enableAlphaTest(true);
	tigl::shader->enableTexture(true);
	tigl::shader->enableLighting(true);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, (float)196 / 255, (float)255 / 255, 1);
}

void Update()
{
}

void Draw()
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw all GameObjects each frame
	for (const GameObject& gameObject : gameObjects)
	{
		gameObject.Draw();
	}
}
