#include "GUIManager.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "PcPart.hpp"
#include "ComputerController.h"
#include "CPU.hpp"
#include "GPU.hpp"
#include "RAM.hpp"

std::vector<CPU> cpuList;
std::vector<GPU> gpuList;
std::vector<RAM> ramList;
std::vector<PcPart*> pcParts;

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

	// Create CPU objects and add them to the list
	cpuList.push_back(CPU("AMD Ryzen 5", CpuSocketType::AMD));
	cpuList.push_back(CPU("AMD Ryzen 7", CpuSocketType::AMD));
	cpuList.push_back(CPU("Intel Core i5", CpuSocketType::INTEL));
	cpuList.push_back(CPU("Intel Core i7", CpuSocketType::INTEL));

	// Create GPU objects and add them to the list
	gpuList.push_back(GPU("NVIDIA GeForce RTX 3080"));
	gpuList.push_back(GPU("AMD Radeon RX 6800 XT"));
	gpuList.push_back(GPU("Geforce RTX 3060"));
	gpuList.push_back(GPU("AMD Radeon RX 5700 "));

	// Create RAM objects and add them to the list
	ramList.push_back(RAM("Corsair Vengeance", RamSocketType::DDR4));
	ramList.push_back(RAM("G.SKILL Ripjaws V", RamSocketType::DDR4));
	ramList.push_back(RAM("ValueRam 2 x 8", RamSocketType::DDR4));
	ramList.push_back(RAM("Trident Z royal 2 x 16", RamSocketType::DDR4));

	// Add CPU, GPU, and RAM objects to the pcParts list
	pcParts.push_back(&cpuList[0]);


	controller.setCurrentObject(GameObject("models/car/honda_jazz.obj"));
}

void GUIManager::update()
{
	// Clear background
	/*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);*/

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (showMenuScreen)
	{
		drawMenuScreen();
	}
	else if (showTutorialScreen)
	{
		drawTutorialScreen();
	}
	else if (showPcBuilderScreen)
	{
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

enum Mode
{
	Mode_Copy,
	Mode_Move,
	Mode_Swap
};
enum PartType
{
	Null_Part,
	CPU,
	GPU,
	RAM
};

int mode = Mode_Copy;
int partType = Null_Part;


void GUIManager::drawPCBuilderScreen()
{
	ImGui::Text("CPU's");

	for (int n = 0; n < cpuList.size(); n++)
	{
		ImGui::PushID(n);

		if (ImGui::Button(cpuList[n].getName().c_str(), ImVec2(250, 20)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			partType = CPU;
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", cpuList[n].getName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
	}

	ImGui::Text("GPU's");

	for (int n = 0; n < gpuList.size(); n++)
	{
		ImGui::PushID(n);

		if (ImGui::Button(gpuList[n].getName().c_str(), ImVec2(250, 20)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			partType = GPU;
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", gpuList[n].getName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
	}

	ImGui::Text("RAM");

	for (int n = 0; n < ramList.size(); n++)
	{
		ImGui::PushID(n);
		if (ImGui::Button(ramList[n].getName().c_str(), ImVec2(250, 20)));


		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			partType = RAM;
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", ramList[n].getName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
	}



	ImGui::Text("Chosen Pc parts");
	for (int n = 0; n < pcParts.size(); n++)
	{
		ImGui::PushID(n);

		ImGui::Button(pcParts[n]->getName().c_str(), ImVec2(250, 20));

		
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
			{
				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_n = *(const int*)payload->Data;
		
				std::cout << "Part type received: "<< partType << std::endl;
				if (partType == CPU)
				{
					pcParts.push_back(&cpuList[payload_n]);
				}
				else if (partType == GPU)
				{
					pcParts.push_back(&gpuList[payload_n]);
				}
				else if (partType == RAM)
				{

					pcParts.push_back(&ramList[payload_n]);
				}
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::PopID();
	}
}
