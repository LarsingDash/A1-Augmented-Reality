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

//Methods
//Init
void Init();

//Update
void Update();
void UpdateKeys();

//Draw
void Draw();

//Other
void GetObjectDir();

//Default window size, will be overridden by fullscreen values
int windowWidth = 700;
int windowHeight = 700;

//temp rotate var
float angleX = 0.f;
float angleY = 0.f;
float angleZ = 0.f;
glm::mat4 rotate = glm::mat4(1.0f);
glm::vec3 rotations = glm::vec3(0, 0, 0);
glm::mat4 translate = glm::mat4(1.0f);
glm::vec3 cubePosition(0, 0, 0);

std::vector<GameObject> gameObjects = std::vector<GameObject>();
std::string objectDir;

GLFWwindow* window;

//Main
int main()
{
	//Get object directory path
	GetObjectDir();

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
	Init();

	//Create test object
	// gameObjects.push_back(GameObject("game_objects/cube/cube.obj"));
	gameObjects.push_back(GameObject(objectDir, "TestCube"));
	gameObjects.push_back(GameObject(objectDir, "OtherCube"));

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

//Init
void Init()
{
	//Init
	tigl::init();

	//Viewport
	tigl::shader->setProjectionMatrix(glm::perspective(
		glm::radians(75.f),
		static_cast<float>(windowWidth) / static_cast<float>(windowHeight),
		0.1f,
		100.f
	));

	//Camera position
	tigl::shader->setViewMatrix(glm::lookAt(
		glm::vec3(0, 0, 5),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	));

	//Light
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setShinyness(25);

	//Camera Light
	tigl::shader->setLightDirectional(0, false);
	tigl::shader->setLightPosition(0, glm::vec3(0,0,5));
	tigl::shader->setLightAmbient(0, glm::vec3(0.25f, 0.25f, 0.25f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.9f, 0.9f, 0.9f));

	//GL settings
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 196.f / 255.f, 255.f / 255.f, 1);
}

//Updates
void Update()
{
	UpdateKeys();

	// tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.f), glm::vec3(cubePosition)));
	rotate = glm::rotate(rotate, glm::radians(angleZ), glm::vec3(0.f, 0.f, 1.f));
	rotate = glm::rotate(rotate, glm::radians(angleY), glm::vec3(0.f, 1.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(angleX), glm::vec3(1.f, 0.f, 0.f));
}

void UpdateKeys()
{
	if (glfwGetKey(window, GLFW_KEY_X))
		angleX += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_Y))
		angleY += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_Z))
		angleZ += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		cubePosition.x -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		cubePosition.x += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_UP))
		cubePosition.y += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		cubePosition.y -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_F))
		cubePosition.z += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_B))
		cubePosition.z -= 0.1f;

	if (!glfwGetKey(window, GLFW_KEY_X) && !glfwGetKey(window, GLFW_KEY_Y) && !glfwGetKey(window, GLFW_KEY_Z))
	{
		angleX = 0;
		angleY = 0;
		angleZ = 0;
	}
}

//Draw
void Draw()
{
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const auto& gameObject : gameObjects)
	{
		gameObject.Draw(cubePosition, rotate);
	}
}

//Other
void GetObjectDir()
{
	const std::string target = "A1-Augmented-Reality";
	const std::string exe = ".exe";
	std::vector<std::string> dirs = std::vector<std::string>();
	dirs.emplace_back("x64\\Release");
	dirs.emplace_back("x64\\Debug");
	dirs.emplace_back("32\\Release");
	dirs.emplace_back("x64\\Debug");

	bool isInProjDir = false;

	char buffer[MAX_PATH];
	GetModuleFileNameA(nullptr, buffer, MAX_PATH);

	//Convert buffer to string
	std::string path;
	constexpr int size = sizeof(buffer) / sizeof(char);

	//Convert buffer to string (keep going till "exe" is found)
	for (const char letter : buffer)
	{
		//Add
		path += letter;

		for (const auto& dir : dirs)
		{
			if (path.length() > dir.size())
			{
				std::string end = path.substr(path.length() - dir.size(), path.length());
				if (end == dir)
				{
					isInProjDir = true;
					path = path.substr(0, path.length() - end.length());
					break;
				}
			}
		}
		if (isInProjDir) break;

		//Find "exe"
		if (path.length() >= exe.size())
		{
			std::string end = path.substr(path.length() - exe.size(), path.length());
			if (end == exe)
			{
				isInProjDir = false;
				path = path.substr(0, path.length() - target.length() - exe.length());
				break;
			}
		}
	}

	objectDir = path;
	std::cout << "Path: " << objectDir << std::endl;
	std::cout << "Dir: " << (isInProjDir ? "Yes" : "No") << std::endl;
}
