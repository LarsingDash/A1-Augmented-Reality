#pragma once

#include <GLFW/glfw3.h>

class GUIManager {
public:
    GUIManager(GLFWwindow* window);

    void init();
    void update();
    void draw();

private:
    GLFWwindow* window;
    bool showMenuScreen = true;
    bool showTutorialScreen = false;
    bool showPcBuilderScreen = false;

    void drawMenuScreen();
    void drawTutorialScreen();
    void drawPCBuilderScreen();
};