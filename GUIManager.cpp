#include "GUIManager.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "PcPart.hpp"
#include "ComputerController.h"

//GameObject currentObject;

GUIManager::GUIManager(GLFWwindow* window, ComputerController controller)
    : window(window), controller(controller)
{
}

void GUIManager::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    controller.setCurrentObject(GameObject("models/car/honda_jazz.obj"));
    
}
void GUIManager::update()
{
    // Clear achtergrond
    /*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);*/

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (showMenuScreen) {
        drawMenuScreen();
    }
    else if (showTutorialScreen) {
        drawTutorialScreen();
    }
    else if (showPcBuilderScreen) {
        drawPCBuilderScreen();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::draw()
{
    
}

void GUIManager::drawMenuScreen()
{
    ImGui::SetNextWindowSize(ImVec2(1350, 750));

    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("PC builder application").x) * 0.5f);
    ImGui::SetCursorPosY((ImGui::GetWindowSize().y - ImGui::CalcTextSize("PC builder application").y) * 0.5f);
    
    ImGui::Text("PC builder application");

    ImGui::Spacing();

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 150.0f) * 0.5f);

    if (ImGui::Button("Tutorial", ImVec2(150, 30)))
    {
        showMenuScreen = false;
        showTutorialScreen = true;
    }
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 150.0f) * 0.5f);

    if (ImGui::Button("PC Builder", ImVec2(150, 30)))
    {
        showMenuScreen = false;
        showTutorialScreen = false;
        showPcBuilderScreen = true;
    }

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 100.0f) * 0.5f);

    if (ImGui::Button("Exit", ImVec2(100, 30)))
    {
        glfwSetWindowShouldClose(window, true);
    }

    ImGui::End();
}


void GUIManager::drawTutorialScreen()
{
    ImGui::Begin("Tutorial");


    ImGui::Text("Welcome to the tutorial screen!");
    ImGui::ShowDemoWindow();

    if (ImGui::Button("Back to Menu"))
    {
        showMenuScreen = true;
        showTutorialScreen = false;
    }


    ImGui::End();
}



void GUIManager::drawPCBuilderScreen()
{
    //ImGui::Begin("Components chooser", nullptr, ImGuiWindowFlags_NoTitleBar);

    float buttonPosX = (ImGui::GetWindowSize().x - 150.0f) * 0.5f;
    float buttonPosY = (ImGui::GetWindowSize().y - 30.0f) * 0.5f;

    static int selectedCPU = -1;
    static int selectedGPU = -1;
    static int selectedPowerSupply = -1;
    static int selectedMotherboard = -1;
    static int selectedRAM = -1;

    std::string cpuText;
    std::string gpuText;
    std::string powerSupplyText;
    std::string motherboardText;
    std::string ramText;

    switch (selectedCPU)
    {
    case 0:
        cpuText = "AMD Ryzen 5 5600X";
        break;
    case 1:
        cpuText = "Intel Core i7-10700K";
        break;
    case 2:
        cpuText = "AMD Ryzen 7 5800X";
        break;
    default:
        cpuText = "";
        break;
    }

    switch (selectedGPU)
    {
    case 0:
        gpuText = "NVIDIA GeForce RTX 3080";
        break;
    case 1:
        gpuText = "AMD Radeon RX 6800 XT";
        break;
    case 2:
        gpuText = "NVIDIA GeForce RTX 3070";
        break;
    default:
        gpuText = "";
        break;
    }

    switch (selectedPowerSupply)
    {
    case 0:
        powerSupplyText = "Corsair RM750";
        break;
    case 1:
        powerSupplyText = "EVGA SuperNOVA 850 G3";
        break;
    case 2:
        powerSupplyText = "Seasonic Focus GX-750";
        break;
    default:
        powerSupplyText = "";
        break;
    }

    switch (selectedMotherboard)
    {
    case 0:
        motherboardText = "ASUS ROG Strix B550-F Gaming";
        break;
    case 1:
        motherboardText = "GIGABYTE X570 AORUS Elite";
        break;
    case 2:
        motherboardText = "MSI MPG Z490 Gaming Edge WiFi";
        break;
    default:
        motherboardText = "";
        break;
    }

    switch (selectedRAM)
    {
    case 0:
        ramText = "G.SKILL Trident Z RGB 16GB DDR4 3600MHz";
        break;
    case 1:
        ramText = "Corsair Vengeance RGB Pro 32GB (2 x 16GB) DDR4 3200MHz";
        break;
    case 2:
        ramText = "Crucial Ballistix RGB 16GB DDR4 3200MHz";
        break;
    default:
        ramText = "";
        break;
    }

    //ImGui::End();

    //ImGui::BeginChild("LeftWindow", ImVec2(ImGui::GetWindowWidth() * 0.25f, ImGui::GetWindowHeight()), true); 
    ImGui::Begin("Components chooser", nullptr, ImGuiWindowFlags_NoTitleBar);

    if (ImGui::CollapsingHeader("CPU's"))
    {
        ImGui::RadioButton("AMD Ryzen 5 5600X", &selectedCPU, 0);
        ImGui::RadioButton("Intel Core i7-10700K", &selectedCPU, 1);
        ImGui::RadioButton("AMD Ryzen 7 5800X", &selectedCPU, 2);
    }

    if (ImGui::CollapsingHeader("GPU's"))
    {
        ImGui::RadioButton("NVIDIA GeForce RTX 3080", &selectedGPU, 0);
        ImGui::RadioButton("AMD Radeon RX 6800 XT", &selectedGPU, 1);
        ImGui::RadioButton("NVIDIA GeForce RTX 3070", &selectedGPU, 2);
    }

    if (ImGui::CollapsingHeader("Power Supplies"))
    {
        ImGui::RadioButton("Corsair RM750", &selectedPowerSupply, 0);
        ImGui::RadioButton("EVGA SuperNOVA 850 G3", &selectedPowerSupply, 1);
        ImGui::RadioButton("Seasonic Focus GX-750", &selectedPowerSupply, 2);
    }

    if (ImGui::CollapsingHeader("Motherboards"))
    {
        ImGui::RadioButton("ASUS ROG Strix B550-F Gaming", &selectedMotherboard, 0);
        ImGui::RadioButton("GIGABYTE X570 AORUS Elite", &selectedMotherboard, 1);
        ImGui::RadioButton("MSI MPG Z490 Gaming Edge WiFi", &selectedMotherboard, 2);
    }

    if (ImGui::CollapsingHeader("RAM"))
    {
        ImGui::RadioButton("G.SKILL Trident Z RGB 16GB DDR4 3600MHz", &selectedRAM, 0);
        ImGui::RadioButton("Corsair Vengeance RGB Pro 32GB (2 x 16GB) DDR4 3200MHz", &selectedRAM, 1);
        ImGui::RadioButton("Crucial Ballistix RGB 16GB DDR4 3200MHz", &selectedRAM, 2);
    }

    //ImGui::EndChild();
    ImGui::End();

    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 400.0f, 0.0f));
    //ImGui::BeginChild("DebugWindow", ImVec2(400.0f, 250.0f), true);
    ImGui::Begin("Navigation Buttons", nullptr, ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Build Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
    {
        //currentObject.changeColor(glm::vec4(1.0, 0.0f, 0.0f, 1.0f));
        controller.setIsDrawing(true);
    }

    if (ImGui::Button("Cinematic Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
    {
        //currentObject.changeColor(glm::vec4(0.0, 1.0f, 0.0f, 1.0f));

    }

    if (ImGui::Button("Show PC part list", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
    {
        showPcPartList = !showPcPartList; 
    }

    if (showPcPartList)
    {
        ImGui::Text("Pc parts list:");
        ImGui::Text("CPU: "); ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", cpuText.c_str());
        ImGui::Text("GPU: "); ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", gpuText.c_str());
        ImGui::Text("PSU: "); ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", powerSupplyText.c_str());
        ImGui::Text("MBU: "); ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "%s", motherboardText.c_str());
        ImGui::Text("RAM: "); ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%s", ramText.c_str());
    }

    ImGui::SetCursorPos(ImVec2((ImGui::GetWindowWidth() / 2) - 75, ImGui::GetWindowHeight() - 70));

    if (ImGui::Button("PC Builder", ImVec2(150, 30)))
    {
    }
    
    ImGui::SetCursorPos(ImVec2((ImGui::GetWindowWidth() / 2) - 75, ImGui::GetWindowHeight() - 35));
    if (ImGui::Button("Back to Menu", ImVec2(150, 30)))
    {
        showMenuScreen = true;
        showTutorialScreen = false;
        showPcBuilderScreen = false;
    }

    //ImGui::EndChild();
    ImGui::End();

    /*ImGui::Begin("PC Builder", nullptr, ImGuiWindowFlags_NoTitleBar);

    ImGui::SetCursorPos(ImVec2(buttonPosX, buttonPosY));

    if (ImGui::Button("PC Builder", ImVec2(150, 30)))
    {
    }

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 100.0f) * 0.5f);
    if (ImGui::Button("Back to Menu", ImVec2(100, 30)))
    {
        showMenuScreen = true;
        showTutorialScreen = false;
        showPcBuilderScreen = false;
    }

    ImGui::End();*/
}