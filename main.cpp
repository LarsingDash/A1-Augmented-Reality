#include "GameObject.h"

#include <iostream>

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
float angle_x = 0.f;
float angle_y = 0.f;
float angle_z = 0.f;
glm::mat4 rotate = glm::mat4(1.0f);
glm::vec3 rotations = glm::vec3(0, 0, 0);
glm::mat4 translate = glm::mat4(1.0f);
glm::vec3 cube_position(0, 0, 0);

std::vector<GameObject> gameObjects = std::vector<GameObject>();

GLFWwindow* window;

int main()
{
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
	gameObjects.push_back(GameObject("game_objects/cube/cube.obj"));

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
		glm::vec3(0, 2, -5),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	));

	//Shader settings
	tigl::shader->enableColor(true);
	tigl::shader->enableAlphaTest(true);
	tigl::shader->enableTexture(true);

	//GL settings
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, (float)196 / 255, (float)255 / 255, 1);
	
}

void Update()
{
	
}
void check_keys()
{
	if (glfwGetKey(window, GLFW_KEY_X))
		angle_x += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_Y))
		angle_y += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_Z))
		angle_z += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		cube_position.x += 0.1;
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		cube_position.x -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_UP))
		cube_position.y += 0.1;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		cube_position.y -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_F))
		cube_position.z += 0.1;
	if (glfwGetKey(window, GLFW_KEY_B))
		cube_position.z -= 0.1;
}
void Draw()
{
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	rotate = glm::mat4(1.0f); // Initialize the transformation matrix
	
	check_keys();

	if (!glfwGetKey(window, GLFW_KEY_X) && !glfwGetKey(window, GLFW_KEY_Y) && !glfwGetKey(window, GLFW_KEY_Z))
	{
		angle_x = 0;
		angle_y = 0;
		angle_z = 0;
	}
	



	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.f), glm::vec3(cube_position)));
	rotate = glm::rotate(rotate, glm::radians(angle_z), glm::vec3(0.f, 0.f, 1.f));
	rotate = glm::rotate(rotate, glm::radians(angle_y), glm::vec3(0.f, 1.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(angle_x), glm::vec3(1.f, 0.f, 0.f));
	
	
	

	for (const GameObject& gameObject : gameObjects)
	{
		gameObject.Draw(rotate);
	}

	//trans = glm::translate(trans, glm::vec3(-translate_x, -translate_y, -translate_z));
	//glm::vec3 empty_vec = glm::vec3(1.f, 1.f, 1.f);	//Draw all GameObjects each frame
	
	
}
