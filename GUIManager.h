#pragma once

#include "GameObject.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"

class GUIManager {
public:
    GUIManager(GLFWwindow* window, GameObject currentObject);

    void init();
    void update();
    void draw();

private:
    GLFWwindow* window;
    GameObject currentObject;
    bool showMenuScreen = true;
    bool showTutorialScreen = false;
    bool showPcBuilderScreen = false;
    bool showPcPartList = false;

    void drawMenuScreen();
    void drawTutorialScreen();
    void drawPCBuilderScreen();
};