#include "GUIManager.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "PcPart.hpp"
#include "ComputerController.h"
#include "CPU.hpp"
#include "GPU.hpp"

//GameObject currentObject;
std::vector<CPU> cpuList;
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
	cpuList.push_back(CPU("Intel core I5", SocketType::INTEL));
	cpuList.push_back(CPU("AMD Ryzen 3", SocketType::AMD));
	cpuList.push_back(CPU("Intel core I3", SocketType::INTEL));
	CPU* cpu1 = new CPU("Intel Core i5", SocketType::INTEL);
	pcParts.push_back(cpu1);

	CPU* cpu2 = new CPU("AMD Ryzen 7", SocketType::AMD);
	pcParts.push_back(cpu2);

	// Create GPU objects and add them to the list
	GPU* gpu1 = new GPU("NVIDIA GeForce RTX 3080");
	pcParts.push_back(gpu1);

	GPU* gpu2 = new GPU("AMD Radeon RX 6800 XT");
	pcParts.push_back(gpu2);

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
int mode = Mode_Copy;


// Add CPU objects to the array

void GUIManager::drawPCBuilderScreen()
{
	
	if (ImGui::TreeNode("Drag and drop to copy/swap items"))
	{
		
		for (int n = 0; n < cpuList.size(); n++)
		{
			std::cout << "CPU LIST SIZE" << cpuList.size() << std::endl;
			ImGui::PushID(n);

			ImGui::Button(cpuList[n].getName().c_str(), ImVec2(70, 20));

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));

				if (mode == Mode_Copy) { ImGui::Text("Copy %s", cpuList[n].getName().c_str()); }
				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int payload_n = *(const int*)payload->Data;
					if (mode == Mode_Copy)
					{
						cpuList[n] = cpuList[payload_n];
					}
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::PopID();
		}
		for (int m = 0; m < cpuList.size(); m++)
		{
			ImGui::PushID(m);

			ImGui::Button(cpuList[m].getName().c_str(), ImVec2(150, 20));

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &m, sizeof(int));

				if (mode == Mode_Copy) { ImGui::Text("Copy %s", cpuList[m].getName().c_str()); }
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int payload_m = *(const int*)payload->Data;

					if (mode == Mode_Copy)
					{
						if (payload_m >= 0 && payload_m < cpuList.size())
						{
							cpuList[m] = cpuList[payload_m];
						}
					}
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::PopID();
		}

		ImGui::TreePop();
	}

}
