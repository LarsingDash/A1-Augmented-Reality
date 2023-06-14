#include "GameObject.h"

#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"
#include "ComputerController.h"

#include "hand.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

//Methods
//Init
void Init();

//Other
void GetObjectDir();
void reset_position();

//Default window size, will be overridden by fullscreen values
int windowWidth = 700;
int windowHeight = 700;

//temp rotate var
glm::vec3 rotations = glm::vec3(0, 0, 0);
glm::mat4 translate = glm::mat4(1.0f);


std::vector<GameObject> gameObjects = std::vector<GameObject>();
std::string objectDir;

GLFWwindow* window;
ComputerController controller = ComputerController(false);

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

	GUIManager guiManager = GUIManager(window, controller);
	guiManager.init();

	//Init
	Init();

	//Create test object
	guiManager.controller.objects.emplace_back(objectDir, "Case");
	guiManager.controller.objects.emplace_back(objectDir, "CPU");
	guiManager.controller.objects.emplace_back(objectDir, "Fan");
	guiManager.controller.objects.emplace_back(objectDir, "GPU");
	guiManager.controller.objects.emplace_back(objectDir, "HDD");
	guiManager.controller.objects.emplace_back(objectDir, "MB");
	guiManager.controller.objects.emplace_back(objectDir, "PSU");
	guiManager.controller.objects.emplace_back(objectDir, "RAM");
	guiManager.controller.objects.emplace_back(objectDir, "SSD");

	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//Program cycle
		HandUpdate();
		guiManager.Draw(window);

		//glfw cycle
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Termination
	HandTeardown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}

//Init
void Init()
{
	//Init
	tigl::init();
	glewInit();

	HandInit(windowWidth, windowHeight);

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
	tigl::shader->setLightPosition(0, glm::vec3(0, 0, 5));
	tigl::shader->setLightAmbient(0, glm::vec3(1, 1, 1));
	tigl::shader->setLightDiffuse(0, glm::vec3(1, 1, 1));
	// tigl::shader->setLightSpecular(0, glm::vec3(1, 1, 1));

	//GL settings
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 196.f / 255.f, 255.f / 255.f, 1);
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
