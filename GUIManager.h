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
    RAM_TYPE
};
class GUIManager {
public:
    GUIManager(GLFWwindow* window, const ComputerController& controller);

    void init();
    void Draw(GLFWwindow* window);
    ComputerController controller;

private:
    GLFWwindow* window;
    bool showMenuScreen = true;
    bool showTutorialScreen = false;
    bool showPcBuilderScreen = false;
    bool showPcPartList = false;

    void drawMenuScreen();
    void drawTutorialScreen();
    void drawPCBuilderScreen();
    void drawAddPartButton();
    void drawDeletePartButton();
    template <typename T>
    void drawPartList(const std::vector<T>& partsList, int partType);
 
};
