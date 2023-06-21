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
std::vector<Storage> ssdList;
std::vector<Storage> hddList;
std::vector<Fan> fanList;
std::vector<PcPart*> pcParts;

CPU* pickedCPU = nullptr;
GPU* pickedGPU = nullptr;
PSU* pickedPSU = nullptr;
RAM* pickedRAM = nullptr;
Motherboard* pickedMotherboard = nullptr;
Storage* pickedSSD = nullptr;
Storage* pickedHDD = nullptr;
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

	cpuList.push_back(CPU("Level 1 AMD CPU", CpuSocketType::AMD, "CPU", 1));
	cpuList.push_back(CPU("Level 2 Intel CPU", CpuSocketType::INTEL, "CPU", 2));
	cpuList.push_back(CPU("Level 3 AMD CPU", CpuSocketType::AMD, "CPU", 3));

	fanList.push_back(Fan("Level 1 FAN", "FAN", 1));
	fanList.push_back(Fan("Level 2 FAN", "FAN", 2));
	fanList.push_back(Fan("Level 3 FAN", "FAN", 3));

	mbuList.push_back(Motherboard("Level 1 AMD MBD", CpuSocketType::AMD, RamSocketType::DDR3, "MB", 1));
	mbuList.push_back(Motherboard("Level 2 AMD MBD", CpuSocketType::AMD, RamSocketType::DDR4, "MB", 2));
	mbuList.push_back(Motherboard("Level 3 INTEL MBD", CpuSocketType::INTEL, RamSocketType::DDR4, "MB", 3));

	gpuList.push_back(GPU("Level 1 GPU", "GPU", 1));
	gpuList.push_back(GPU("Level 2 GPU", "GPU", 2));
	gpuList.push_back(GPU("Level 3 GPU", "GPU", 3));

	ramList.push_back(RAM("Level 1 DDR3 RAM", RamSocketType::DDR3, "RAM", 1));
	ramList.push_back(RAM("Level 2 DDR4 RAM", RamSocketType::DDR4, "RAM", 2));
	ramList.push_back(RAM("Level 3 DDR4 RAM", RamSocketType::DDR4, "RAM", 3));

	psuList.push_back(PSU("Level 1 PSU", "PSU", 1));
	psuList.push_back(PSU("Level 2 PSU", "PSU", 2));
	psuList.push_back(PSU("Level 3 PSU", "PSU", 3));

	pcCaseList.push_back(PcCase("Level 1 PC Case", "Case", 1));
	pcCaseList.push_back(PcCase("Level 2 PC Case", "Case", 2));
	pcCaseList.push_back(PcCase("Level 3 PC Case", "Case", 3));

	ssdList.push_back(Storage("Level 1 SSD", "SSD", 1));
	ssdList.push_back(Storage("Level 2 SSD", "SSD", 2));
	ssdList.push_back(Storage("Level 3 SSD", "SSD", 3));

	hddList.push_back(Storage("Level 1 HDD", "HDD", 1));
	hddList.push_back(Storage("Level 2 HDD", "HDD", 2));
	hddList.push_back(Storage("Level 3 HDD", "HDD", 3));
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
		controller.stopCinematicMode();
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
		controller.changeRotationX(24);

	ImGui::SetCursorPos(ImVec2(windowSize.x - buttonSize.x - padding, y));
	while (ImGui::Button("Right", buttonSize))
		controller.changeRotationY(24);

	ImGui::SetCursorPos(ImVec2(x, windowSize.y - buttonSize.y - padding));
	while (ImGui::Button("Bottom", buttonSize))
		controller.changeRotationX(-24);

	ImGui::SetCursorPos(ImVec2(padding, y));
	while (ImGui::Button("Left", buttonSize))
		controller.changeRotationY(-24);

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
		if (showCompatability)
		{
			showCompatability = false;
		}
		else
		{
			showCompatability = true;
		}
	}
	if (showCompatability)
	{
		if (pickedCPU == nullptr)
			ImGui::TextWrapped(
				"CPU ISSUE: No CPU selected, this is the heart of the computer and it wont function without it.");
		ImGui::Spacing();

		if (pickedFan == nullptr)
			ImGui::TextWrapped(
				"FAN ISSUE: No fan selected, your pc will boot without one but it will quickly crash due to overheating which will greatly wear down your CPU");
		ImGui::Spacing();

		if (pickedGPU == nullptr)
			ImGui::TextWrapped(
				"GPU TIP: No GPU selected. This is definitely not essential but you might want to consider picking one if you are planning on gaming");
		ImGui::Spacing();

		if (pickedRAM == nullptr)
			ImGui::TextWrapped("RAM ISSUE: No RAM selected. Memory is an essential component for a pc");
		ImGui::Spacing();

		if (pickedMotherboard != nullptr)
		{
			if (pickedRAM != nullptr)
			{
				if (pickedRAM->socketType != pickedMotherboard->ramSocketType)
				{
					ImGui::TextWrapped(
						"INCOMPATIBILITY ISSUE: You have picked incompatible sockets for your RAM and motherboard. You're trying to match DDR3 with DDR4. Make sure the RAM types match");
					ImGui::Spacing();
				}
			}
			if (pickedCPU != nullptr)
			{
				if (pickedCPU->socketType != pickedMotherboard->socketType)
				{
					ImGui::TextWrapped(
						"INCOMPATIBILITY ISSUE: You have picked incompatible sockets for your CPU and motherboard. You're trying to match and AMD socket with an Intel socket. Make sure the CPU socket types match");
					ImGui::Spacing();
				}
			}
		}
		else
			ImGui::TextWrapped(
				"MOTHERBOARD ISSUE: No motherboard selected, this part is essential for allowing communication between your selected pc parts");
		ImGui::Spacing();

		if (pickedPSU == nullptr)
			ImGui::TextWrapped("PSU ISSUE: No PSU selected, this part is necessary to power your components.");
		ImGui::Spacing();

		if (pickedCase == nullptr)
			ImGui::TextWrapped(
				"CASE WARNING: No case is selected. You need a case to safely house and ventilate your components");
		ImGui::Spacing();

		if (pickedSSD == nullptr)
			ImGui::TextWrapped(
				"SSD ISSUE: No ssd selected. You storage to be able to boot an operating system");
		ImGui::Spacing();

		if (pickedHDD == nullptr)
			ImGui::TextWrapped(
				"HDD ISSUE: No hdd selected. You storage to be able to boot an operating system");
		ImGui::Spacing();
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

	ImGui::Text("SSD");
	drawPartList(ssdList, SSD_TYPE);

	ImGui::Text("HDD");
	drawPartList(hddList, HDD_TYPE);

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
		controller.stopCinematicMode();
	}

	if (ImGui::Button("Cinematic Mode", ImVec2(ImGui::GetItemRectSize().x, 25.0f)))
	{
		isCinematicMode = true;
		isBuildMode = false;
		controller.startCinematicMode();
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
		controller.objects.emplace_back(directory, objectPath, part->getTier());
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
			else if (partType == SSD_TYPE)
			{
				std::cout << "Storage type received: " << partType << std::endl;
				if (pickedSSD != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedSSD), pcParts.end());
				}
				pickedSSD = &ssdList[payload_n];
				pcParts.push_back(&ssdList[payload_n]);
			}
			else if (partType == HDD_TYPE)
			{
				std::cout << "Storage type received: " << partType << std::endl;
				if (pickedHDD != nullptr)
				{
					pcParts.erase(std::remove(pcParts.begin(), pcParts.end(), pickedHDD), pcParts.end());
				}
				pickedHDD = &hddList[payload_n];
				pcParts.push_back(&hddList[payload_n]);
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
			std::string partName = pcParts[payload_n]->getName().c_str();
			for (CPU& cpu : cpuList)
			{
				if (cpu.getName() == partName)
				{
					pickedCPU = nullptr; // Set pickedCPU to nullptr
					break;
				}
			}

			for (Fan& fan : fanList)
			{
				if (fan.getName() == partName)
				{
					pickedFan = nullptr; // Set pickedFan to nullptr
					break;
				}
			}

			for (RAM& ram : ramList)
			{
				if (ram.getName() == partName)
				{
					pickedRAM = nullptr; // Set pickedRAM to nullptr
					break;
				}
			}

			for (GPU& gpu : gpuList)
			{
				if (gpu.getName() == partName)
				{
					pickedGPU = nullptr; // Set pickedGPU to nullptr
					break;
				}
			}

			for (Motherboard& mbu : mbuList)
			{
				if (mbu.getName() == partName)
				{
					pickedMotherboard = nullptr; // Set pickedMotherboard to nullptr
					break;
				}
			}

			for (PSU& psu : psuList)
			{
				if (psu.getName() == partName)
				{
					pickedPSU = nullptr; // Set pickedPSU to nullptr
					break;
				}
			}

			for (PcCase& pcCase : pcCaseList)
			{
				if (pcCase.getName() == partName)
				{
					pickedCase = nullptr; // Set pickedCase to nullptr
					break;
				}
			}

			for (Storage& ssd : ssdList)
			{
				if (ssd.getName() == partName)
				{
					pickedSSD = nullptr; // Set pickedStorage to nullptr
					break;
				}
			}
			for (Storage& hdd : hddList)
			{
				if (hdd.getName() == partName)
				{
					pickedHDD = nullptr; // Set pickedStorage to nullptr
					break;
				}
			}
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
