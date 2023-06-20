#include "GUIManager.h"

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "PcPart.hpp"
#include "ComputerController.h"
#include "CPU.hpp"
#include "Fan.hpp"
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
std::vector<Fan> fanList;
std::vector<PcPart*> pcParts;

CPU* pickedCPU = nullptr;
GPU* pickedGPU = nullptr;
PSU* pickedPSU = nullptr;
RAM* pickedRAM = nullptr;
Motherboard* pickedMotherboard = nullptr;
Storage* pickedStorage = nullptr;
Fan* pickedFan = nullptr;
PcCase* pickedCase = nullptr;


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

	cpuList.push_back(CPU("Level 1 AMD CPU", CpuSocketType::AMD, "CPU"));
	cpuList.push_back(CPU("Level 2 Intel CPU", CpuSocketType::INTEL, "path2"));
	cpuList.push_back(CPU("Level 3 AMD CPU", CpuSocketType::AMD, "path3"));

	fanList.push_back(Fan("Level 1 FAN", "FAN"));
	fanList.push_back(Fan("Level 2 FAN", "path2"));
	fanList.push_back(Fan("Level 3 FAN", "path3"));

	mbuList.push_back(Motherboard("Level 1 AMD MBD", MbuSocketType::AMD, RamSocketType::DDR3, "MB"));
	mbuList.push_back(Motherboard("Level 2 AMD MBD", MbuSocketType::AMD, RamSocketType::DDR4, "path6"));
	mbuList.push_back(Motherboard("Level 3 AMD MBD", MbuSocketType::INTEL, RamSocketType::DDR4, "path7"));

	gpuList.push_back(GPU("Level 1 GPU", "GPU"));
	gpuList.push_back(GPU("Level 2 GPU", "path10"));
	gpuList.push_back(GPU("Level 3 GPU", "path11"));

	ramList.push_back(RAM("Level 1 DDR3 RAM", RamSocketType::DDR3, "RAM"));
	ramList.push_back(RAM("Level 2 DDR4 RAM", RamSocketType::DDR4, "path14"));
	ramList.push_back(RAM("Level 3 DDR4 RAM", RamSocketType::DDR4, "path15"));

	psuList.push_back(PSU("Level 1 PSU", "PSU"));
	psuList.push_back(PSU("Level 2 PSU", "path18"));
	psuList.push_back(PSU("Level 3 PSU", "path19"));

	pcCaseList.push_back(PcCase("Level 1 PC Case", "Case"));
	pcCaseList.push_back(PcCase("Level 2 PC Case", "path22"));
	pcCaseList.push_back(PcCase("Level 3 PC Case", "path23"));

	storageList.push_back(Storage("Level 1 Storage", "SSD"));
	storageList.push_back(Storage("Level 2 Storage", "path26"));
	storageList.push_back(Storage("Level 3 Storage", "path27"));

}

void GUIManager::Draw(GLFWwindow* window)
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

	controller.handleDraw(window);

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
	if (isBuildMode)
	{
		ImGui::Begin("PC Builder");

		drawPartSelectionList();

		drawBuilderTopRight();

		drawChosenPcPartsList();

		drawCompatabilityInterface();

		ImGui::End();
	}
	else if (isCinematicMode)
	{
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Cinematic View", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		drawCinematicViewControls();

		drawBuilderTopRight();
		ImGui::End();

	}
}


void GUIManager::drawCinematicViewControls()
{
	// Calculate the button positions
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 buttonSize(100, 100);
	float padding = 10.0f;
	float x = (windowSize.x - buttonSize.x) * 0.5f;
	float y = (windowSize.y - buttonSize.y) * 0.5f;

	// Set button style
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4 greenColor(0.0f, 0.8f, 0.0f, 1.0f); 
	ImVec4 greenColor2(0.0f, 0.6f, 0.0f, 0.7f);
	ImVec4 whiteColor(1.0f, 1.0f, 1.0f, 1.0f); 

	ImVec4 originalButtonColor = style.Colors[ImGuiCol_Button];
	ImVec4 originalButtonHoveredColor = style.Colors[ImGuiCol_ButtonHovered];
	ImVec4 originalButtonActiveColor = style.Colors[ImGuiCol_ButtonActive];
	ImVec4 originalTextColor = style.Colors[ImGuiCol_Text];

	style.Colors[ImGuiCol_Button] = greenColor;
	style.Colors[ImGuiCol_ButtonHovered] = greenColor2;
	style.Colors[ImGuiCol_ButtonActive] = greenColor;
	style.Colors[ImGuiCol_Text] = whiteColor;

	// Draw the buttons
	ImGui::SetCursorPos(ImVec2(x, padding));
	while (ImGui::Button("Top", buttonSize))
	{
		std::cout << "Rotating upwards" << std::endl;
		// Handle button click for rotating upwards
	}

	ImGui::SetCursorPos(ImVec2(windowSize.x - buttonSize.x - padding, y));
	while (ImGui::Button("Right", buttonSize))
	{
		std::cout << "Rotating Right" << std::endl;

		// Handle button click  for rotating right
	}

	ImGui::SetCursorPos(ImVec2(x, windowSize.y - buttonSize.y - padding));
	while (ImGui::Button("Bottom", buttonSize))
	{
		std::cout << "Rotating downwards" << std::endl;

		// Handle button click for rotating downwards
	}

	ImGui::SetCursorPos(ImVec2(padding, y));
	while (ImGui::Button("Left", buttonSize))
	{
		std::cout << "Rotating left" << std::endl;

		// Handle button click for rotating left
	}

	// Restore the original style
	style.Colors[ImGuiCol_Button] = originalButtonColor;
	style.Colors[ImGuiCol_ButtonHovered] = originalButtonHoveredColor;
	style.Colors[ImGuiCol_ButtonActive] = originalButtonActiveColor;
	style.Colors[ImGuiCol_Text] = originalTextColor;

	ImGui::End();
}


void GUIManager::drawCompatabilityInterface()
{
	if (ImGui::Button("Show Compatibility Tips", ImVec2(ImGui::GetItemRectSize().x, 60.0f)))
	{
		if(showCompatability)
		{
			showCompatability = false;
		}else
		{
			showCompatability = true;
		}
	}
	if(showCompatability)
	{
		ImGui::Text("Hello compatibility");
		if (pickedCPU != nullptr)
			ImGui::Text(pickedCPU->getName().c_str());
		else
			ImGui::Text("No CPU selected");

		if (pickedFan != nullptr)
			ImGui::Text(pickedFan->getName().c_str());
		else
			ImGui::Text("No fan selected");

		if (pickedGPU != nullptr)
			ImGui::Text(pickedGPU->getName().c_str());
		else
			ImGui::Text("No GPU selected");
		if (pickedRAM != nullptr)
			ImGui::Text(pickedRAM->getName().c_str());
		else
			ImGui::Text("No RAM selected");

		if (pickedMotherboard != nullptr)
			ImGui::Text(pickedMotherboard->getName().c_str());
		else
			ImGui::Text("No motherboard selected");

		if (pickedPSU != nullptr)
			ImGui::Text(pickedPSU->getName().c_str());
		else
			ImGui::Text("No PSU selected");

		if (pickedCase != nullptr)
			ImGui::Text(pickedCase->getName().c_str());
		else
			ImGui::Text("No case selected");

		if (pickedStorage != nullptr)
			ImGui::Text(pickedStorage->getName().c_str());
		else
			ImGui::Text("No storage selected");
	}

}


void GUIManager::drawPartSelectionList()
{
	//Top left window
	ImGui::Begin("Components chooser", nullptr, ImGuiWindowFlags_NoTitleBar);

	ImGui::Text("Processors");
	drawPartList(cpuList, CPU_TYPE);

	ImGui::Text("Cpu coolers");
	drawPartList(fanList, FAN_TYPE);

	ImGui::Text("Memory modules");
	drawPartList(ramList, RAM_TYPE);

	ImGui::Text("Graphics cards");
	drawPartList(gpuList, GPU_TYPE);

	ImGui::Text("Mother boards");
	drawPartList(mbuList, MBU_TYPE);

	ImGui::Text("Power supplies");
	drawPartList(psuList, PSU_TYPE);

	ImGui::Text("Pc cases");
	drawPartList(pcCaseList, PC_CASE_TYPE);

	ImGui::Text("Storage");
	drawPartList(storageList, STORAGE_TYPE);


	drawAddPartButton();

	ImGui::End();
}
void GUIManager::drawBuilderTopRight()
{
	//Top right window
	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 400.0f, 0.0f));
	ImGui::Begin("Navigation Buttons", nullptr, ImGuiWindowFlags_NoTitleBar);

	if (ImGui::Button("Build Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		isBuildMode = true;
		isCinematicMode = false;
	}

	if (ImGui::Button("Cinematic Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		isCinematicMode = true;
		isBuildMode = false;

	}


	if (ImGui::Button("DRAW NEW OBJECTS", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		setPcObjects();
	}
	if (ImGui::Button("CLEAR OBJECTS", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		clearPcObjects();
	}
}
void GUIManager::drawChosenPcPartsList()
{
	ImGui::Text("Chosen Pc parts");

	for (int n = 0; n < pcParts.size(); n++)
	{
		ImGui::PushID(n);
		if (ImGui::Button(pcParts[n]->getName().c_str(), ImVec2(250, 40)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", pcParts[n]->getName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
	}

	drawDeletePartButton();
}

void GUIManager::setPcObjects()
{
	clearPcObjects();
	for (const PcPart* part : pcParts)
	{
		std::string objectPath = part->getObjectPath();
		controller.objects.emplace_back(directory, objectPath);
	}
}

void GUIManager::clearPcObjects()
{
	controller.objects.clear();
}

void GUIManager::drawAddPartButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.8f, 0.2f, 1.0f)); // Set button color to green
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.9f, 0.3f, 1.0f));
	// Set button hover color to a lighter green
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.7f, 0.1f, 1.0f));
	// Set button active color to a darker green

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
				if (pickedCPU != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedCPU), pcParts.end());
				}
				pickedCPU = &cpuList[payload_n];
				pcParts.push_back(&cpuList[payload_n]);
				
			}
			else if (partType == FAN_TYPE)
			{
				std::cout << "FAN type received: " << partType << std::endl;
				if (pickedFan != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedFan), pcParts.end());
				}
				pickedFan = &fanList[payload_n];
				pcParts.push_back(&fanList[payload_n]);
			}
			else if (partType == GPU_TYPE)
			{
				std::cout << "GPU type received: " << partType << std::endl;
				if (pickedGPU != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedGPU), pcParts.end());
				}
				pickedGPU = &gpuList[payload_n];
				pcParts.push_back(&gpuList[payload_n]);
			}
			else if (partType == RAM_TYPE)
			{
				std::cout << "RAM type received: " << partType << std::endl;
				if (pickedRAM != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedRAM), pcParts.end());
				}
				pickedRAM = &ramList[payload_n];
				pcParts.push_back(&ramList[payload_n]);
			}
			else if (partType == PC_CASE_TYPE)
			{
				std::cout << "PC case type received: " << partType << std::endl;
				if (pickedCase != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedCase), pcParts.end());
				}
				pickedCase = &pcCaseList[payload_n];
				pcParts.push_back(&pcCaseList[payload_n]);
			}
			else if (partType == MBU_TYPE)
			{
				std::cout << "Motherboard type received: " << partType << std::endl;
				if (pickedMotherboard != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedMotherboard), pcParts.end());
				}
				pickedMotherboard = &mbuList[payload_n];
				pcParts.push_back(&mbuList[payload_n]);
			}
			else if (partType == PSU_TYPE)
			{
				std::cout << "PSU type received: " << partType << std::endl;
				if (pickedPSU != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedPSU), pcParts.end());
				}
				pickedPSU = &psuList[payload_n];
				pcParts.push_back(&psuList[payload_n]);
			}
			else if (partType == STORAGE_TYPE)
			{
				std::cout << "Storage type received: " << partType << std::endl;
				if (pickedStorage != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedStorage), pcParts.end());
				}
				pickedStorage = &storageList[payload_n];
				pcParts.push_back(&storageList[payload_n]);
			}
			setPcObjects();
		}
		ImGui::EndDragDropTarget();
	}
}

void GUIManager::drawDeletePartButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f)); // Set button color to red
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f));
	// Set button hover color to a lighter red
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 1.0f));
	// Set button active color to a darker red

	if (ImGui::Button("Delete Part", ImVec2(250, 40)))
	{
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
			setPcObjects();
		}

		ImGui::EndDragDropTarget();
	}
}

template <typename T>
void GUIManager::drawPartList(const std::vector<T>& partsList, int part)
{
	for (int n = 0; n < partsList.size(); n++)
	{
		ImGui::PushID(n);
		if (ImGui::Button(partsList[n].getName().c_str(), ImVec2(110, 40)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			partType = part;
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", partsList[n].getName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
		if (n + 1 < partsList.size())
		{
			ImGui::SameLine();
		}
	}
}
