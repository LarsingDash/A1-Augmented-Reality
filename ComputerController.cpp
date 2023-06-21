#include "ComputerController.h"
glm::mat4 rotate = glm::mat4(1.0f);
glm::vec3 cubePosition(0, 0, 0);


ComputerController::ComputerController(bool newIsDrawing) {
	setIsDrawing(newIsDrawing);
}

void ComputerController::setIsDrawing(bool newIsDrawing) {
	isDrawing = newIsDrawing;
}
void ComputerController::startCinematicMode()
{
	angle_X = 0.f;
	angle_Y = 20.f;
	angle_Z = 0.f;
	cin_mode = true;
}

void ComputerController::stopCinematicMode()
{
	cin_mode = false;
	angle_Y = 20.f;
	rotate = glm::rotate(glm::mat4(1.f), glm::radians(angle_Y), glm::vec3(0, 1, 0));
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
			cubePosition.x -= 0.1f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
			cubePosition.x += 0.1f;
		if (glfwGetKey(window, GLFW_KEY_UP))
			cubePosition.y += 0.1f;
		if (glfwGetKey(window, GLFW_KEY_DOWN))
			cubePosition.y -= 0.1f;
		if (glfwGetKey(window, GLFW_KEY_F))
			cubePosition.z += 0.1f;
		if (glfwGetKey(window, GLFW_KEY_B))
			cubePosition.z -= 0.1f;
		if (glfwGetKey(window, GLFW_KEY_R))
			reset_position();
		changeRotation();
	}
}

void ComputerController::reset_position()
{
	angle_X = 0.f;
	angle_Y = 0.f;
	angle_Z = 0.f;
}

void ComputerController::changeRotation()
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
			object.Draw(glm::vec3(cubePosition.x, cubePosition.y, cubePosition.z - 7), rotate);
		}
	}
}
