#include "ComputerController.h"

#include <iostream>

ComputerController::ComputerController(bool newIsDrawing)
{
	setIsDrawing(newIsDrawing);
}

void ComputerController::setIsDrawing(bool newIsDrawing)
{
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
	changeRotationY(24);
}

void ComputerController::HandleKeys(GLFWwindow* window)
{
	if (cin_mode)
	{
		if (glfwGetKey(window, GLFW_KEY_X))
		{
			angleX += 0.2f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_Y))
		{
			angleY += 0.2f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_Z))
		{
			angleZ += 0.2f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT))
		{
			translation.x -= 0.1f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
		{
			translation.x += 0.1f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_UP))
		{
			translation.y += 0.1f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN))
		{
			translation.y -= 0.1f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_F))
		{
			translation.z += 0.1f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_B))
		{
			translation.z -= 0.1f;
			UpdateRotation();
		}
		if (glfwGetKey(window, GLFW_KEY_R))
		{
			ResetRotation();
			UpdateRotation();
		}
	}
}

constexpr float ROTATION_SPEED = 0.25f;
constexpr float MAX_ROTATION_SPEED = 6;

void ComputerController::UpdateTargets()
{
	if (abs(targetX - angleX) > 0.01f)
	{
		isRotatingX = true;

		const float difference = targetX - angleX;
		const float move =
			difference > 0
				? std::min(difference * ROTATION_SPEED, MAX_ROTATION_SPEED)
				: std::max(difference * ROTATION_SPEED, -MAX_ROTATION_SPEED);

		angleX += move;
		UpdateRotation();
	}
	else if (isRotatingX)
	{
		isRotatingX = false;
		angleX = targetX;
	}

	if (abs(targetY - angleY) > 0.01f)
	{
		isRotatingY = true;

		const float difference = targetY - angleY;
		const float max = difference > 0 ? MAX_ROTATION_SPEED : MAX_ROTATION_SPEED * -1;

		const float move =
			difference > 0
			? std::min(difference * ROTATION_SPEED, MAX_ROTATION_SPEED)
			: std::max(difference * ROTATION_SPEED, -MAX_ROTATION_SPEED);

		angleY += move;
		UpdateRotation();
	}
	else if (isRotatingY)
	{
		isRotatingY = false;
		angleY = targetY;
	}
}

void ComputerController::ResetRotation()
{
	targetX = 0.f;
	targetY = 0.f;
	targetZ = 0.f;
}
void ComputerController::resetTranslation()
{
	translation = glm::vec3(0, 0, 0);
}
void ComputerController::changeRotationX(const float x)
{
	targetX += x;

	if (targetX > 180)
	{
		targetX = 180 - (targetX - 180);
		targetX *= -1;

		angleX = 180 - (angleX - 180);
		angleX *= -1;
	}
	else if (targetX < -180)
	{
		targetX = -180 - (targetX + 180);
		targetX *= -1;

		angleX = -180 - (angleX + 180);
		angleX *= -1;
	}
}

void ComputerController::changeRotationY(const float y)
{
	targetY += y;

	if (targetY > 180)
	{
		targetY = 180 - (targetY - 180);
		targetY *= -1;

		angleY = 180 - (angleY - 180);
		angleY *= -1;
	}
	else if (targetY < -180)
	{
		targetY = -180 - (targetY + 180);
		targetY *= -1;

		angleY = -180 - (angleY + 180);
		angleY *= -1;
	}
}

void ComputerController::changeRotationZ(const float z)
{
	targetZ += z;
}

void ComputerController::changePosition(const glm::vec3 pos)
{
	translation += pos;
}

void ComputerController::UpdateRotation()
{
	rotate = glm::rotate(glm::mat4(1.f), glm::radians(angleX), glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, glm::radians(angleY), glm::vec3(0, 1, 0));
	rotate = glm::rotate(rotate, glm::radians(angleZ), glm::vec3(0, 0, 1));
}

void ComputerController::handleDraw(GLFWwindow* window)
{
	HandleKeys(window);
	UpdateTargets();

	if (isDrawing)
	{
		for (const auto& object : objects)
		{
			object.Draw(translation, rotate);
		}
	}
}
