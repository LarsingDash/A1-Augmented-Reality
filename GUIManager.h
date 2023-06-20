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
    Mode_Copy,
    Mode_Move,
    Mode_Swap
};

enum PartType
{
    CPU_TYPE,
    GPU_TYPE,
    RAM_TYPE,
    PC_CASE_TYPE,
    PSU_TYPE,
    STORAGE_TYPE,
    MBU_TYPE,
    FAN_TYPE
};
class GUIManager {
public:
    GUIManager(GLFWwindow* window, const ComputerController& controller, std::string objectDirectory);

    void init();
    void Draw(GLFWwindow* window);
    ComputerController controller;

private:
    GLFWwindow* window;
    bool showMenuScreen = true;
    bool showCompatability = false;
    bool showTutorialScreen = false;
    bool showPcBuilderScreen = false;
    bool showPcPartList = false;
    bool isCinematicMode = false;
    bool isBuildMode = true;
    float verticalOffset = 0.f;
    float horizontalOffset = 0.f;
    std::string directory;
    void drawCinematicViewControls();
    void drawPartSelectionList();
    void drawBuilderTopRight();
    void drawChosenPcPartsList();
    void drawMenuScreen();
    void drawTutorialScreen();
    void drawPCBuilderScreen();
    void drawAddPartButton();
    void drawDeletePartButton();
    void drawCompatabilityInterface();
    void setPcObjects();
    void clearPcObjects();
    template <typename T>
    void drawPartList(const std::vector<T>& partsList, int partType);
 
};
