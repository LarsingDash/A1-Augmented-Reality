#include "ComputerController.h"

#include <iostream>

constexpr float ROTATION_SPEED = 0.25f;
constexpr float MAX_ROTATION_SPEED = 6;
constexpr glm::vec3 MOVEMENT_SPEED = glm::vec3(0.2f);
constexpr glm::vec3 MAX_MOVEMENT_SPEED = glm::vec3(0.0625f, 0.0625f, 0.0625f);

//Constructor
ComputerController::ComputerController(const bool isDrawing)
{
	SetIsDrawing(isDrawing);
}

//Updates
void ComputerController::HandleDraw(GLFWwindow* window)
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

		glm::vec3 move = difference * MOVEMENT_SPEED;
		move = clamp(move, -MAX_MOVEMENT_SPEED, MAX_MOVEMENT_SPEED);

		trans += move;
	}
	else if (isMoving)
	{
		isMoving = false;
		trans = targetTrans;
	}
}

void ComputerController::UpdateRotation()
{
	rotate = glm::rotate(glm::mat4(1.f), glm::radians(angleX), glm::vec3(1, 0, 0));
	rotate = glm::rotate(rotate, glm::radians(angleY), glm::vec3(0, 1, 0));
	rotate = glm::rotate(rotate, glm::radians(angleZ), glm::vec3(0, 0, 1));
}

//Resets
void ComputerController::ResetRotation()
{
	targetX = 0.f;
	targetY = 0.f;
	targetZ = 0.f;
}

void ComputerController::ResetTranslation()
{
	targetTrans = glm::vec3(0, 0, 0);
}

//Setters
void ComputerController::SetIsDrawing(const bool drawing)
{
	isDrawing = drawing;
}

void ComputerController::SetCinematicMode(const bool cinState)
{
	cinematicMode = cinState;

	if (cinematicMode) {
		ResetRotation();
		ResetTranslation();
		UpdateRotation();
	} else
	{
		ResetRotation();
		ResetTranslation();
		ChangeRotationY(24);
	}
}

//Transformations
void ComputerController::ChangeRotationX(const float x)
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

void ComputerController::ChangeRotationY(const float y)
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

void ComputerController::ChangeRotationZ(const float z)
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

void ComputerController::ChangePosition(const glm::vec3 pos)
{
	targetTrans += pos;
}