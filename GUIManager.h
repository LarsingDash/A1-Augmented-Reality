#pragma once
#include <GLFW/glfw3.h>

class GUIManager
{
public:
    GUIManager(GLFWwindow* window);

    void init();
    void update();
    void draw();

private:
    GLFWwindow* window;
};
