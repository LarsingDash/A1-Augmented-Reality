#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

using tigl::Vertex;


#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

void update();
void draw();

const int width = 700;
const int height = 700;

GLFWwindow* window;

void initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

int main()
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
	});

	//First time shaders
	tigl::shader->setProjectionMatrix(glm::perspective(
		glm::radians(90.f),
		(float)width / height,
		0.1f,
		100.f
	));

	tigl::shader->setViewMatrix(glm::lookAt(
		glm::vec3(0, 0, 5),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	));
	tigl::shader->enableColor(true);
	tigl::shader->enableAlphaTest(true);
	glClearColor(0, (float)196 / 255, (float)255 / 255, 1);

	initImGui();

	//MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		//program cycle
		update();
		draw();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();

		static bool show_window = true;


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//glfw cycle
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Termination
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}


void update()
{
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	tigl::begin(GL_TRIANGLES);
	tigl::addVertex(Vertex::PC(glm::vec3(-2, -1, -4), glm::vec4(1, 0, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(2, -1, -4), glm::vec4(0, 1, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 1, -4), glm::vec4(0, 0, 1, 1)));

	tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, 10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

	tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(10, -1, -10), glm::vec4(1, 1, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

	tigl::end();
}
