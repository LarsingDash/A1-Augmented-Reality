#pragma once
#include <vector>
#include "GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class ComputerController
{
public:
	float angle_X = 0.f;
	float angle_Y = 20.f;
	float angle_Z = 0.f;
	bool cin_mode = false;
	ComputerController(bool isDrawing);
	void handleDraw(GLFWwindow* window);
	void update_position(GLFWwindow* window);
	void reset_position();
	void startCinematicMode();
	void stopCinematicMode();
	void changeRotation();
	void setIsDrawing(bool isDrawing);
	std::vector<GameObject> objects;

private:
	bool isDrawing = false;
};

