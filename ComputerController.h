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
		void UpdateTargets();
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

		bool isRotatingX = false;
		bool isRotatingY = false;
		bool isRotatingZ = false;
		bool isMoving = false;

		float targetX = 0.f;
		float targetY = 0.f;
		float targetZ = 0.f;
		glm::vec3 trans{};

		float angleX = targetX;
		float angleY = targetY;
		float angleZ = targetZ;
		glm::vec3 targetTrans{};

		bool cin_mode = false;

		bool isDrawing = false;
};
