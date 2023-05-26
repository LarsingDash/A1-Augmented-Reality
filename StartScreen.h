#pragma once

#include "BaseScreen.h"
#include <GLFW/glfw3.h>

class StartScreen : public BaseScreen
{
public:
	StartScreen(GLFWwindow* window);

private:
	GLFWwindow* window;
};

