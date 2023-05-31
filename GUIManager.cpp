#include "GUIManager.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

GUIManager::GUIManager(GLFWwindow* window)
    : window(window)
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
}
void GUIManager::update()
{
    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
    // Draw your OpenGL content here
}

void GUIManager::drawMenuScreen()
{
    ImGui::SetNextWindowSize(ImVec2(1350, 750));

    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    // Center the text horizontally and vertically
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("PC builder application").x) * 0.5f);
    ImGui::SetCursorPosY((ImGui::GetWindowSize().y - ImGui::CalcTextSize("PC builder application").y) * 0.5f);

    // Increase the text size and thickness using ImGui::SetWindowFontScale and ImGui::PushStyleVar
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
    ImGui::Begin("PC Builder", nullptr, ImGuiWindowFlags_NoTitleBar);

    float buttonPosX = (ImGui::GetWindowSize().x - 150.0f) * 0.5f;
    float buttonPosY = (ImGui::GetWindowSize().y - 30.0f) * 0.5f;

    static int selectedCPU = -1;
    static int selectedGPU = -1;
    static int selectedPowerSupply = -1;
    static int selectedMotherboard = -1;
    static int selectedRAM = -1;


    switch (selectedCPU)
    {
    case 0:
        // CPU 1 selected
        break;
    case 1:
        // CPU 2 selected
        break;
    case 2:
        // CPU 3 selected
        break;
    default:
        // No CPU selected
        break;
    }

    switch (selectedGPU)
    {
    case 0:
        // GPU 1 selected
        break;
    case 1:
        // GPU 2 selected
        break;
    case 2:
        // GPU 3 selected
        break;
    default:
        // No GPU selected
        break;
    }

    switch (selectedPowerSupply)
    {
    case 0:
        // Power supply 1 selected
        break;
    case 1:
        // Power supply 2 selected
        break;
    case 2:
        // Power supply 3 selected
        break;
    default:
        // No power supply selected
        break;
    }

    switch (selectedMotherboard)
    {
    case 0:
        // Motherboard 1 selected
        break;
    case 1:
        // Motherboard 2 selected
        break;
    case 2:
        // Motherboard 3 selected
        break;
    default:
        // No motherboard selected
        break;
    }

    switch (selectedRAM)
    {
    case 0:
        // RAM 1 selected
        break;
    case 1:
        // RAM 2 selected
        break;
    case 2:
        // RAM 3 selected
        break;
    default:
        // No RAM selected
        break;
    }
    ImGui::BeginChild("LeftWindow", ImVec2(ImGui::GetWindowWidth() * 0.25f, ImGui::GetWindowHeight()), true);

    if (ImGui::CollapsingHeader("CPU's"))
    {
        ImGui::RadioButton("CPU 1", &selectedCPU, 0);
        ImGui::RadioButton("CPU 2", &selectedCPU, 1);
        ImGui::RadioButton("CPU 3", &selectedCPU, 2);
    }

    if (ImGui::CollapsingHeader("GPU's"))
    {
        ImGui::RadioButton("GPU 1", &selectedGPU, 0);
        ImGui::RadioButton("GPU 2", &selectedGPU, 1);
        ImGui::RadioButton("GPU 3", &selectedGPU, 2);
    }

    if (ImGui::CollapsingHeader("Power Supplies"))
    {
        ImGui::RadioButton("Power supply 1", &selectedPowerSupply, 0);
        ImGui::RadioButton("Power supply 2", &selectedPowerSupply, 1);
        ImGui::RadioButton("Power supply 3", &selectedPowerSupply, 2);
    }

    if (ImGui::CollapsingHeader("Motherboards"))
    {
        ImGui::RadioButton("Motherboard 1", &selectedMotherboard, 0);
        ImGui::RadioButton("Motherboard 2", &selectedMotherboard, 1);
        ImGui::RadioButton("Motherboard 3", &selectedMotherboard, 2);
    }

    if (ImGui::CollapsingHeader("RAM"))
    {
        ImGui::RadioButton("RAM 1", &selectedRAM, 0);
        ImGui::RadioButton("RAM 2", &selectedRAM, 1);
        ImGui::RadioButton("RAM 3", &selectedRAM, 2);
    }

    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 300.0f, 0.0f));
    ImGui::BeginChild("DebugWindow", ImVec2(300.0f, 250.0f), true);

    if (ImGui::Button("Build Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
    {
    }

    if (ImGui::Button("Cinematic Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
    {
    }

    if (ImGui::Button("Show PC part list", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
    {
    }


    ImGui::Text("Pc parts list:");
    ImGui::Text("CPU: "); ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "TEST");
    ImGui::Text("GPU: "); ImGui::SameLine();
    ImGui::Text("Test");
    ImGui::Text("Power supply: "); ImGui::SameLine();
    ImGui::Text("Test");
    ImGui::Text("Motherboard: "); ImGui::SameLine();
    ImGui::Text("Test");
    ImGui::Text("RAM: "); ImGui::SameLine();
    ImGui::Text("Test");
    ImGui::SetCursorPos(ImVec2(buttonPosX, buttonPosY));

    if (ImGui::Button("PC Builder", ImVec2(150, 30)))
    {
    }

    ImGui::EndChild();

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

    ImGui::End();
}