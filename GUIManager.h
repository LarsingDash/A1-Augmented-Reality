#pragma once

#include "ComputerController.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"
#include "ImageLoader.h"

class GUIManager {
public:
    GUIManager(GLFWwindow* window, ComputerController controller);

    void init();
    void update();
    void draw();

private:
    GLFWwindow* window;
    ComputerController controller;
    ImageLoader loader;
    bool showMenuScreen = true;
    bool showTutorialScreen = false;
    bool showHandgesturesScreen = false;
    bool showPcPartScreen = false;
    bool showPcBuilderScreen = false;
    bool showPcPartList = false;

    void drawMenuScreen();
    void drawTutorialScreen();
    void drawPCBuilderScreen();
};