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
	void ResetRotation();
	void startCinematicMode();
	void stopCinematicMode();
	void changeRotationX(const float x);
	void changeRotationY(const float y);
	void changeRotationZ(const float z);
	void changePosition(const glm::vec3 pos);
	void setIsDrawing(bool isDrawing);
	std::vector<GameObject> objects;

private:
	void UpdateRotation();

	glm::mat4 rotate = glm::mat4(1.0f);
	glm::vec3 translation{ 0, 0, 0 };

	float angle_X = 0.f;
	float angle_Y = 20.f;
	float angle_Z = 0.f;
	bool cin_mode = false;

	bool isDrawing = false;
};

