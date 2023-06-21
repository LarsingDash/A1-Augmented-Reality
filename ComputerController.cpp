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
	changePosition(glm::vec3(0.25f, 0.25, 0));
	ResetRotation();
	UpdateRotation();
}

void ComputerController::stopCinematicMode()
{
	cin_mode = false;

	ResetRotation();
	changeRotationY(24);
}

constexpr float ROTATION_SPEED = 0.25f;
constexpr float MAX_ROTATION_SPEED = 6;
constexpr glm::vec3 MOVEMENT_SPEED = glm::vec3(0.25f, 0.25f, 0.25f);
constexpr glm::vec3 MAX_MOVEMENT_SPEED = glm::vec3(0.0625f, 0.0625f, 0.0625f);

void ComputerController::UpdateTargets()
{
	//Rotation X
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

	//Rotation Y
	if (abs(targetY - angleY) > 0.01f)
	{
		isRotatingY = true;

		const float difference = targetY - angleY;

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

	//Rotation Z
	if (abs(targetZ - angleZ) > 0.01f)
	{
		isRotatingZ = true;

		const float difference = targetZ - angleZ;

		const float move =
			difference > 0
				? std::min(difference * ROTATION_SPEED, MAX_ROTATION_SPEED)
				: std::max(difference * ROTATION_SPEED, -MAX_ROTATION_SPEED);

		angleZ += move;
		UpdateRotation();
	}
	else if (isRotatingZ)
	{
		isRotatingZ = false;
		angleZ = targetZ;
	}

	//Translation
	if (distance(targetTrans, trans) > 0.01f)
	{
		isMoving = true;

		const glm::vec3 difference = targetTrans - trans;

		// const glm::vec3 move =
		// 	distance(difference, glm::vec3()) > 0
		// 	? std::min(difference * MOVEMENT_SPEED, MAX_MOVEMENT_SPEED)
		// 	: std::max(difference * MOVEMENT_SPEED, -MAX_MOVEMENT_SPEED);

		const bool largerThanMax = abs(distance(difference, glm::vec3())) > distance(MAX_MOVEMENT_SPEED, glm::vec3());
		const glm::vec3 move = largerThanMax
			                       ? distance(difference, glm::vec3()) > 0
				                         ? MAX_MOVEMENT_SPEED
				                         : -MAX_MOVEMENT_SPEED
			                       : difference;

		trans += move;
	}
	else if (isMoving)
	{
		isMoving = false;
		trans = targetTrans;
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

	if (targetZ > 180)
	{
		targetZ = 180 - (targetZ - 180);
		targetZ *= -1;

		angleZ = 180 - (angleZ - 180);
		angleZ *= -1;
	}
	else if (targetZ < -180)
	{
		targetZ = -180 - (targetZ + 180);
		targetZ *= -1;

		angleZ = -180 - (angleZ + 180);
		angleZ *= -1;
	}
}

void ComputerController::changePosition(const glm::vec3 pos)
{
	targetTrans += pos;
}

void ComputerController::UpdateRotation()
{
	rotate = glm::rotate(glm::mat4(1.f), glm::radians(angleX), glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, glm::radians(angleY), glm::vec3(0, 1, 0));
	rotate = glm::rotate(rotate, glm::radians(angleZ), glm::vec3(0, 0, 1));
}

void ComputerController::handleDraw(GLFWwindow* window)
{
	UpdateTargets();

	if (isDrawing)
	{
		for (const auto& object : objects)
		{
			object.Draw(trans, rotate);
		}
	}
}
