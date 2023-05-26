#pragma once

#include "BaseScreen.h"
#include <GLFW/glfw3.h>

class TutorialScreen : public BaseScreen
{
public:
	TutorialScreen(GLFWwindow* window);

private:
	GLFWwindow* window;
};

