#pragma once
#include <vector>
#include "GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class ComputerController
{
public:
	ComputerController(bool isDrawing);
	void handleDraw(GLFWwindow* window);
	void update_position(GLFWwindow* window);
	void reset_position();

	void setIsDrawing(bool isDrawing);
	std::vector<GameObject> objects;

private:
	bool isDrawing = false;
};

