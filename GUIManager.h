#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GUIManager
{
public:
	GLFWwindow* window;

	void initImGui();
};

#endif // GUI_MANAGER_H
