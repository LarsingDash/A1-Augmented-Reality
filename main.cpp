#include "GameObject.h"

#include <iostream>
#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

using tigl::Vertex;


#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

void OpenGLInit();

void Update();
void Draw();

//Default window size, will be overridden by fullscreen values
int windowWidth = 700;
int windowHeight = 700;

//temp rotate var
float angleX = 0.f;
float angleY = 0.f;
float angleZ = 0.f;
glm::mat4 trans;

std::vector<GameObject> gameObjects = std::vector<GameObject>();

GLFWwindow* window;

int main()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::cout << buffer << std::endl;

	//Test initiate glfw
	if (!glfwInit())
		throw "Could not initialize glwf";

	//Get primary monitor size so that the fullscreen application can have the correct resolution
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	glfwGetMonitorWorkarea(monitor, nullptr, nullptr, &windowWidth, &windowHeight);

	window = glfwCreateWindow(windowWidth, windowHeight, "A1 Augmented Reality", monitor, nullptr);

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

	//Create test object
	// gameObjects.push_back(GameObject("game_objects/cube/cube.obj"));
	gameObjects.push_back(GameObject("C:\\Users\\larsv\\Desktop\\components\\cube\\cube.obj"));

	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//Program cycle
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

void OpenGLInit()
{
	//Init
	tigl::init();

	//Viewport
	tigl::shader->setProjectionMatrix(glm::perspective(
		glm::radians(90.f),
		(float) windowWidth / (float) windowHeight,
		0.1f,
		100.f
	));

	//Camera position
	tigl::shader->setViewMatrix(glm::lookAt(
		glm::vec3(0, 2, 5),
		glm::vec3(0, 1.5, 0),
		glm::vec3(0, 1, 0)
	));

	//Shader settings
	tigl::shader->enableAlphaTest(true);

	//GL settings
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, (float)196 / 255, (float)255 / 255, 1);
}

void Update()
{
	trans = glm::mat4(1.0f); // Initialize the transformation matrix

	if (glfwGetKey(window, GLFW_KEY_X))
	{
		angleX += 5.f;
	}

	if (glfwGetKey(window, GLFW_KEY_Y))
	{
		angleY += 5.f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_Z))
	{
		angleZ += 5.f;
	}

	trans = glm::rotate(trans, glm::radians(angleZ), glm::vec3(0.f, 0.f, 1.f));
	trans = glm::rotate(trans, glm::radians(angleY), glm::vec3(0.f, 1.f, 0.f));
	trans = glm::rotate(trans, glm::radians(angleX), glm::vec3(1.f, 0.f, 0.f));
}

void Draw()
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw
	for (const GameObject& gameObject : gameObjects)
	{
		gameObject.Draw(trans);
	}
}
