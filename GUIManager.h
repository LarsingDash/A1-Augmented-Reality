#pragma once

#include "ComputerController.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"
#include "PcPart.hpp"
enum Mode
{
	MODE_COPY,
	MODE_MOVE,
	MODE_SWAP
};

enum PartType
{
	CPU_TYPE,
	GPU_TYPE,
	RAM_TYPE,
	PC_CASE_TYPE,
	PSU_TYPE,
	SSD_TYPE,
	HDD_TYPE,
	MBU_TYPE,
	FAN_TYPE
};

class GuiManager
{
	public:
		GuiManager(GLFWwindow* window, const ComputerController& controller, std::string objectDirectory);

		void Init() const;
		void Draw();

		ComputerController controller;

	private:
		GLFWwindow* window;
		std::string directory;

		bool showMenuScreen = true;
		bool showCompatibility = false;
		bool showTutorialScreen = false;
		bool showPcBuilderScreen = false;

		bool isCinematicMode = false;
		bool isBuildMode = true;

		void DrawCinematicViewControls();
		void DrawPartSelectionList();
		void DrawBuilderTopRight();
		void DrawChosenPcPartsList();
		void DrawMenuScreen();
		void DrawTutorialScreen();
		void DrawPcBuilderScreen();
		void DrawAddPartButton();
		void DrawDeletePartButton();
		void DrawCompatibilityInterface();

		void SetPcObjects();
		void ClearPcObjects();

		template <typename T>
		void DrawPartList(const std::vector<T>& partsList, int partType);
};
