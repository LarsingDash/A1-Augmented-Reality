#pragma once

#include "ComputerController.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GUIManager.h"

class GUIManager {
public:
    GUIManager(GLFWwindow* window, const ComputerController& controller);

    void init();
    void Draw(const glm::vec3& position, const glm::mat4& rotation);
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
};