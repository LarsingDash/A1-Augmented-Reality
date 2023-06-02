#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"
#include "GameObject.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

const int width = 700;
const int height = 700;

GLFWwindow* window;
GameObject cube = GameObject();

void update();
void draw();

int main()
{
    if (!glfwInit())
        throw "Could not initialize glfw";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glfw";
    }
    glfwMakeContextCurrent(window);
    glewInit();

    tigl::init();

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });

    // First time shaders
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

    GUIManager guiManager(window, cube);
    guiManager.init();

    // MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {
        // Program cycle
        update();
        draw();
        guiManager.update();

        // glfw cycle
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Termination
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

void update()
{
}

//float angle = 1.0f;
glm::vec3 cubeColor = glm::vec3(1.0f, 1.0f, 1.0f);

void draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    cube.drawCube();
}
