#pragma once

#include "BaseScreen.h"
#include <GLFW/glfw3.h>

class PcBuilderScreen : public BaseScreen
{
public:
	PcBuilderScreen(GLFWwindow* window);

private:
	GLFWwindow* window;
};

