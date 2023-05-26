#include "GUIManager.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "BaseScreen.h"
#include "StartScreen.h"
#include "PcBuilderScreen.h"
#include "TutorialScreen.h"

ImVector<BaseScreen> screens = ImVector<BaseScreen>();
GLFWwindow* window;

GUIManager::GUIManager(GLFWwindow* window)
    : window(window)
{
}

void addScreens()
{
    StartScreen startScreen = StartScreen(window);
    PcBuilderScreen pcBuilderScreen = PcBuilderScreen(window);
    TutorialScreen tutorialScreen = TutorialScreen(window);

    screens.push_back(startScreen);
    screens.push_back(pcBuilderScreen);
    screens.push_back(tutorialScreen);
}

/// <summary>
/// Initialiseert de ImGui libs voor de juiste versie.
/// </summary>
void GUIManager::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

/// <summary>
/// Update methode om de grafische elementen continu te updaten. (Roep dit aan in de mains while loop)
/// </summary>
void GUIManager::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test");
    ImGui::Text("Hello world");
    ImGui::End();

    static bool show_window = true;
    ImGui::Begin("My Window", &show_window);

    if (ImGui::Button("Save"))
    {
        std::cout << "Button Pressed";
    }

    if (ImGui::Button("Cancel"))
    {
        std::cout << "Button Pressed"; 
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::draw()
{
   
}
