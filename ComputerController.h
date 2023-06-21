#pragma once
#include <vector>
#include "GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class ComputerController
{
	public:
		//Constructor
		ComputerController(bool isDrawing);

		//Updates
		void HandleDraw(GLFWwindow* window);
		void UpdateTargets();

		//Resets
		void ResetRotation();
    	void ResetTranslation();

		//Setters
		void SetIsDrawing(bool drawing);
		void SetCinematicMode(bool cinState);

		//Transformations
		void ChangeRotationX(float x);
		void ChangeRotationY(float y);
		void ChangeRotationZ(float z);
		void ChangePosition(glm::vec3 pos);

		//List of components
		std::vector<GameObject> objects;

	private:
		//Update
		void UpdateRotation();

		//Modes
		bool cinematicMode = false;
		bool isDrawing = false;

		//Keeping track of animations
		bool isRotatingX = false;
		bool isRotatingY = false;
		bool isRotatingZ = false;
		bool isMoving = false;

		//Targets
		float targetX = 0.f;
		float targetY = 0.f;
		float targetZ = 0.f;
		glm::vec3 targetTrans{};

		//Current values
		float angleX = targetX;
		float angleY = targetY;
		float angleZ = targetZ;
		glm::mat4 rotate = glm::mat4(1.0f);
		glm::vec3 trans{};
};
