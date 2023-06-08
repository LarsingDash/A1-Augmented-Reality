#pragma once

#include "ComputerController.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"
#include "PcPart.hpp"

class GUIManager {
public:
    GUIManager(GLFWwindow* window, ComputerController controller);

    void init();
    void update();
    void draw();
private:
    GLFWwindow* window;
    ComputerController controller;
    bool showMenuScreen = true;
    bool showTutorialScreen = false;
    bool showPcBuilderScreen = false;
    bool showPcPartList = false;

    void drawMenuScreen();
    void drawTutorialScreen();
    void drawPCBuilderScreen();
    void createAddPartButton();
    void createDeletePartButton();
    template <typename T>
    void drawPartList(const std::vector<T>& partsList, int partType);

};
