#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

const int width = 700;
const int height = 700;

GLFWwindow* window;

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

    GUIManager guiManager(window);
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

void draw()
{
    glm::vec4 color = glm::vec4(1, 0, 0, 1);
    glm::vec4 colorLeft = glm::vec4(0, 1, 0, 1);
    glm::vec4 colorRight = glm::vec4(0, 0, 1, 1);
    glm::vec4 colorFront = glm::vec4(1, 1, 0, 1);
    glm::vec4 colorUp = glm::vec4(0, 1, 1, 1);

    glm::vec4 bottomLeft = glm::vec4(0, 0, 0, 0);
    glm::vec4 bottomRight = glm::vec4(1, 0, 0, 0);
    glm::vec4 topLeft = glm::vec4(0, 1, 0, 0);
    glm::vec4 topRight = glm::vec4(1, 1, 0, 0);

    glm::vec4 bottomLeftFront = glm::vec4(- 1, - 1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 bottomLeftBack = glm::vec4(- 1, - 1, 0, 1);// *camera->getInverseMatrix();
    glm::vec4 bottomRightFront = glm::vec4(1, - 1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 bottomRightBack = glm::vec4(1, - 1, 0, 1);// *camera->getInverseMatrix();
    glm::vec4 topLeftFront = glm::vec4(- 1, 1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 topLeftBack = glm::vec4(- 1, 1, 0, 1);// *camera->getInverseMatrix();
    glm::vec4 topRightFront = glm::vec4(1, 1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 topRightBack = glm::vec4(1, 1, 0, 1);// *camera->getInverseMatrix();

    tigl::begin(GL_QUADS);
    tigl::addVertex(Vertex::PT(bottomLeftFront, bottomLeft));
    tigl::addVertex(Vertex::PT(bottomRightFront, bottomRight));
    tigl::addVertex(Vertex::PT(bottomRightFront, bottomRight));
    tigl::addVertex(Vertex::PT(topRightBack, topRight));
    tigl::addVertex(Vertex::PT(topRightBack, topRight));
    tigl::addVertex(Vertex::PT(topLeftBack, topLeft));
    tigl::addVertex(Vertex::PT(topLeftBack, topLeft));
    tigl::addVertex(Vertex::PT(bottomLeftFront, bottomLeft));

    tigl::addVertex(Vertex::PT(bottomLeftFront, bottomLeft));
    tigl::addVertex(Vertex::PT(bottomLeftBack, bottomRight));
    tigl::addVertex(Vertex::PT(bottomLeftBack, bottomRight));
    tigl::addVertex(Vertex::PT(topLeftBack, topRight));
    tigl::addVertex(Vertex::PT(topLeftBack, topRight));
    tigl::addVertex(Vertex::PT(topLeftFront, topLeft));
    tigl::addVertex(Vertex::PT(topLeftFront, topLeft));
    tigl::addVertex(Vertex::PT(bottomLeftFront, bottomLeft));

    tigl::addVertex(Vertex::PT(bottomRightFront, bottomRight));
    tigl::addVertex(Vertex::PT(bottomRightBack, bottomLeft));
    tigl::addVertex(Vertex::PT(bottomRightBack, bottomLeft));
    tigl::addVertex(Vertex::PT(topRightBack, topLeft));
    tigl::addVertex(Vertex::PT(topRightBack, topLeft));
    tigl::addVertex(Vertex::PT(topRightFront, topRight));
    tigl::addVertex(Vertex::PT(topRightFront, topRight));
    tigl::addVertex(Vertex::PT(bottomRightFront, bottomRight));

    tigl::addVertex(Vertex::PT(bottomLeftBack, bottomLeft));
    tigl::addVertex(Vertex::PT(bottomRightBack, bottomRight));
    tigl::addVertex(Vertex::PT(bottomRightBack, bottomRight));
    tigl::addVertex(Vertex::PT(topRightBack, topRight));
    tigl::addVertex(Vertex::PT(topRightBack, topRight));
    tigl::addVertex(Vertex::PT(topLeftBack, topLeft));
    tigl::addVertex(Vertex::PT(topLeftBack, topLeft));
    tigl::addVertex(Vertex::PT(bottomLeftBack, bottomLeft));

    tigl::addVertex(Vertex::PT(topLeftFront, bottomLeft));
    tigl::addVertex(Vertex::PT(topRightFront, bottomRight));
    tigl::addVertex(Vertex::PT(topRightFront, bottomRight));
    tigl::addVertex(Vertex::PT(topRightBack, topRight));
    tigl::addVertex(Vertex::PT(topRightBack, topRight));
    tigl::addVertex(Vertex::PT(topLeftBack, topLeft));
    tigl::addVertex(Vertex::PT(topLeftBack, topLeft));
    tigl::addVertex(Vertex::PT(topLeftFront, bottomLeft));

    tigl::end();
}
