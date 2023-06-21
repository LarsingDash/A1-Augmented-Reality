#include "ComputerController.h"

ComputerController::ComputerController(bool newIsDrawing) {
	setIsDrawing(newIsDrawing);
}

void ComputerController::setIsDrawing(bool newIsDrawing) {
	isDrawing = newIsDrawing;
}
void ComputerController::startCinematicMode()
{
	cin_mode = true;

	ResetRotation();
	UpdateRotation();
}

void ComputerController::stopCinematicMode()
{
	cin_mode = false;

	ResetRotation();
	angle_Y = 15.f;
	UpdateRotation();
}

void ComputerController::update_position(GLFWwindow* window)
{
	if (cin_mode)
	{
		if (glfwGetKey(window, GLFW_KEY_X))
			angle_X += 0.2f;
		if (glfwGetKey(window, GLFW_KEY_Y))
			angle_Y += 0.2f;
		if (glfwGetKey(window, GLFW_KEY_Z))
			angle_Z += 0.2f;
		if (glfwGetKey(window, GLFW_KEY_LEFT))
			translation.x -= 0.1f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
			translation.x += 0.1f;
		if (glfwGetKey(window, GLFW_KEY_UP))
			translation.y += 0.1f;
		if (glfwGetKey(window, GLFW_KEY_DOWN))
			translation.y -= 0.1f;
		if (glfwGetKey(window, GLFW_KEY_F))
			translation.z += 0.1f;
		if (glfwGetKey(window, GLFW_KEY_B))
			translation.z -= 0.1f;
		if (glfwGetKey(window, GLFW_KEY_R))
			ResetRotation();
		UpdateRotation();
	}
}

void ComputerController::ResetRotation()
{
	angle_X = 0.f;
	angle_Y = 0.f;
	angle_Z = 0.f;
}

void ComputerController::changeRotationX(const float x)
{
	angle_X += x;
}

void ComputerController::changeRotationY(const float y)
{
	angle_Y += y;
}

void ComputerController::changeRotationZ(const float z)
{
	angle_Z += z;
}

void ComputerController::changePosition(const glm::vec3 pos)
{
	translation += pos;
}

void ComputerController::UpdateRotation()
{
	rotate = glm::rotate(glm::mat4(1.f), glm::radians(angle_X), glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, glm::radians(angle_Y), glm::vec3(0, 1, 0));
	rotate = glm::rotate(rotate, glm::radians(angle_Z), glm::vec3(0, 0, 1));
}

void ComputerController::handleDraw(GLFWwindow* window) {
	update_position(window);

	if (isDrawing) {
		for (const auto& object : objects)
		{
			object.Draw(translation, rotate);
		}
	}
}
