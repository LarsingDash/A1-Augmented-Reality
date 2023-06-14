#include "GUIManager.h"

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "PcPart.hpp"
#include "ComputerController.h"
#include "CPU.hpp"
#include "GPU.hpp"
#include "PcCase.hpp"
#include "PSU.h"
#include "RAM.hpp"
#include "Storage.hpp"
#include "Motherboard.hpp"

std::vector<CPU> cpuList;
std::vector<GPU> gpuList;
std::vector<Motherboard> mbuList;
std::vector<RAM> ramList;
std::vector<PSU> psuList;
std::vector<PcCase> pcCaseList;
std::vector<Storage> storageList;
std::vector<PcPart*> pcParts;

GUIManager::GUIManager(GLFWwindow* window, const ComputerController& controller, std::string objectDirectory)
    : window(window), controller(controller), directory(objectDirectory)
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

	cpuList.push_back(CPU("AMD Ryzen 5", CpuSocketType::AMD, "CPU"));
	cpuList.push_back(CPU("AMD Ryzen 7", CpuSocketType::AMD, "path2"));
	cpuList.push_back(CPU("Intel Core i5", CpuSocketType::INTEL, "path3"));
	cpuList.push_back(CPU("Intel Core i7", CpuSocketType::INTEL, "path4"));

	mbuList.push_back(Motherboard("mbu1", MbuSocketType::AMD, "MB"));
	mbuList.push_back(Motherboard("mbu2", MbuSocketType::AMD, "path6"));
	mbuList.push_back(Motherboard("mbu3", MbuSocketType::INTEL, "path7"));
	mbuList.push_back(Motherboard("mbu4", MbuSocketType::INTEL, "path8"));

	gpuList.push_back(GPU("NVIDIA GeForce RTX 3080", "GPU"));
	gpuList.push_back(GPU("AMD Radeon RX 6800 XT", "path10"));
	gpuList.push_back(GPU("Geforce RTX 3060", "path11"));
	gpuList.push_back(GPU("AMD Radeon RX 5700 ", "path12"));

	ramList.push_back(RAM("Corsair Vengeance", RamSocketType::DDR4, "RAM"));
	ramList.push_back(RAM("G.SKILL Ripjaws V", RamSocketType::DDR4, "path14"));
	ramList.push_back(RAM("ValueRam 2 x 8", RamSocketType::DDR4, "path15"));
	ramList.push_back(RAM("Trident Z royal 2 x 16", RamSocketType::DDR4, "path16"));

	psuList.push_back(PSU("Power Supply Unit 1", "PSU"));
	psuList.push_back(PSU("Power Supply Unit 2", "path18"));
	psuList.push_back(PSU("Power Supply Unit 3", "path19"));
	psuList.push_back(PSU("Power Supply Unit 4", "path20"));

	pcCaseList.push_back(PcCase("PC Case 1", "Case"));
	pcCaseList.push_back(PcCase("PC Case 2", "path22"));
	pcCaseList.push_back(PcCase("PC Case 3", "path23"));
	pcCaseList.push_back(PcCase("PC Case 4", "path24"));

	storageList.push_back(Storage("Storage 1", "SSD"));
	storageList.push_back(Storage("Storage 2", "path26"));
	storageList.push_back(Storage("Storage 3", "path27"));
	storageList.push_back(Storage("Storage 4", "path28"));
}

void GUIManager::Draw(const glm::vec3& position, const glm::mat4& rotation)
{
    // Clear background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    controller.handleDraw(position, rotation);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::drawMenuScreen()
{
    // Get the size of the GLFW window
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));

    ImGui::Begin("Main Menu", nullptr);

    // Center the text vertically and horizontally
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("PC builder application").x) * 0.5f);
    ImGui::SetCursorPosY((ImGui::GetWindowSize().y - ImGui::CalcTextSize("PC builder application").y) * 0.5f);

    ImGui::Text("PC builder application");

    ImGui::Spacing();

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 150.0f) * 0.5f);

    if (ImGui::Button("PC Builder", ImVec2(150, 30)))
    {
        showMenuScreen = false;
        showTutorialScreen = false;
        showPcBuilderScreen = true;
        controller.setIsDrawing(true);
    }
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 150.0f) * 0.5f);

    if (ImGui::Button("Tutorial", ImVec2(150, 30)))
    {
        showMenuScreen = false;
        showTutorialScreen = true;
		showPcBuilderScreen = false;
		controller.setIsDrawing(false);
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


int mode = Mode_Copy;
int partType;


void GUIManager::drawPCBuilderScreen()
{

	//Top left window
	ImGui::Begin("Components chooser", nullptr, ImGuiWindowFlags_NoTitleBar);

	if (ImGui::CollapsingHeader("CPU's"))
	{
		drawPartList(cpuList, CPU_TYPE);

	}

	if (ImGui::CollapsingHeader("RAM"))
	{
		drawPartList(ramList, RAM_TYPE);

	}

	if (ImGui::CollapsingHeader("GPU's"))
	{
		drawPartList(gpuList, GPU_TYPE);

	}

	if (ImGui::CollapsingHeader("Motherboards"))
	{
		drawPartList(mbuList, MBU_TYPE);

	}

	if (ImGui::CollapsingHeader("PSU"))
	{
		drawPartList(psuList, PSU_TYPE);

	}
	if (ImGui::CollapsingHeader("PC CASE"))
	{
		drawPartList(pcCaseList, PC_CASE_TYPE);

	}
	if (ImGui::CollapsingHeader("STORAGE"))
	{
		drawPartList(storageList, STORAGE_TYPE);

	}

	drawAddPartButton();

	ImGui::End();

	//Top right window
	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 400.0f, 0.0f));
	ImGui::Begin("Navigation Buttons", nullptr, ImGuiWindowFlags_NoTitleBar);

	if (ImGui::Button("Build Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		controller.setIsDrawing(true);
	}

	if (ImGui::Button("Cinematic Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{

	}


	if (ImGui::Button("DRAW NEW OBJECTS", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		pcDrawObjects();

	}
	if (ImGui::Button("CLEAR OBJECTS", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		pcClearObjects();

	}
	ImGui::Text("Chosen Pc parts");

	for (int n = 0; n < pcParts.size(); n++)
	{
		ImGui::PushID(n);
		if (ImGui::Button(pcParts[n]->getName().c_str(), ImVec2(250, 20)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", pcParts[n]->getName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
	}

	// for (int n = 0; n < pcParts.size(); n++)
	// {
	// 	ImGui::Button(pcParts[n]->getName().c_str(), ImVec2(250, 20));
	//
	// }
	drawDeletePartButton();

	ImGui::End();

}
void GUIManager::pcDrawObjects() {
	pcClearObjects();
	for (const PcPart* part : pcParts)
	{
		std::string objectPath = part->getObjectPath();
		controller.objects.emplace_back(directory, objectPath);
	}
}

void GUIManager::pcClearObjects(){
	controller.objects.clear();

}
void GUIManager::drawAddPartButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.8f, 0.2f, 1.0f)); // Set button color to green
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.9f, 0.3f, 1.0f)); // Set button hover color to a lighter green
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.7f, 0.1f, 1.0f)); // Set button active color to a darker green

	ImGui::Button("Add PC Part", ImVec2(250, 40));

	ImGui::PopStyleColor(3); // Pop the three style colors


	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_n = *(const int*)payload->Data;

			std::cout << "Part type received: " << partType << std::endl;
			if (partType == CPU_TYPE)
			{
				std::cout << "CPU type received: " << partType << std::endl;

				pcParts.push_back(&cpuList[payload_n]);
				
				
			}
			else if (partType == GPU_TYPE)
			{
				std::cout << "GPU type received: " << partType << std::endl;

				pcParts.push_back(&gpuList[payload_n]);
			}
			else if (partType == RAM_TYPE)
			{
				std::cout << "RAM type received: " << partType << std::endl;

				pcParts.push_back(&ramList[payload_n]);
			}
			else if (partType == PC_CASE_TYPE)
			{
				std::cout << "PC case type received: " << partType << std::endl;

				pcParts.push_back(&pcCaseList[payload_n]);
			}
			else if (partType == MBU_TYPE)
			{
				std::cout << "Motherboard type received: " << partType << std::endl;

				pcParts.push_back(&mbuList[payload_n]);
			}
			else if (partType == PSU_TYPE)
			{
				std::cout << "PSU type received: " << partType << std::endl;

				pcParts.push_back(&psuList[payload_n]);
			}
			else if (partType == STORAGE_TYPE)
			{
				std::cout << "Storage type received: " << partType << std::endl;

				pcParts.push_back(&storageList[payload_n]);
			}
			pcDrawObjects();
		}
		ImGui::EndDragDropTarget();
	
	}
}
void GUIManager::drawDeletePartButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f)); // Set button color to red
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f)); // Set button hover color to a lighter red
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 1.0f)); // Set button active color to a darker red

	if (ImGui::Button("Delete Part", ImVec2(250, 40)))
	{
		// Perform deletion here if needed
	}

	ImGui::PopStyleColor(3);

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_n = *(const int*)payload->Data;

			// Delete the dragged part from the pcParts vector
			pcParts.erase(pcParts.begin() + payload_n);
		}
		pcDrawObjects();

		ImGui::EndDragDropTarget();
	}
}

template <typename T>
void GUIManager::drawPartList(const std::vector<T>& partsList, int part)
{
	for (int n = 0; n < partsList.size(); n++)
	{
		ImGui::PushID(n);
		if (ImGui::Button(partsList[n].getName().c_str(), ImVec2(250, 40)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			partType = part;
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", partsList[n].getName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
	}
}
