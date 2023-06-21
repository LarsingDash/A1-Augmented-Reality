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

int mode = MODE_COPY;
int partType;

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

GuiManager::GuiManager(GLFWwindow* window, const ComputerController& controller, std::string objectDirectory)
	: window(window), controller(controller), directory(objectDirectory)
{
}

void GuiManager::Init() const
{
	//ImGUI setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	const ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//Filling in all component lists
	cpuList.emplace_back("Level 1 AMD CPU", CpuSocketType::AMD, "CPU", 1);
	cpuList.emplace_back("Level 2 Intel CPU", CpuSocketType::INTEL, "CPU", 2);
	cpuList.emplace_back("Level 3 AMD CPU", CpuSocketType::AMD, "CPU", 3);

	fanList.emplace_back("Level 1 FAN", "FAN", 1);
	fanList.emplace_back("Level 2 FAN", "FAN", 2);
	fanList.emplace_back("Level 3 FAN", "FAN", 3);

	mbuList.emplace_back("Level 1 AMD MBD", CpuSocketType::AMD, RamSocketType::DDR3, "MB", 1);
	mbuList.emplace_back("Level 2 AMD MBD", CpuSocketType::AMD, RamSocketType::DDR4, "MB", 2);
	mbuList.emplace_back("Level 3 INTEL MBD", CpuSocketType::INTEL, RamSocketType::DDR4, "MB", 3);

	gpuList.emplace_back("Level 1 GPU", "GPU", 1);
	gpuList.emplace_back("Level 2 GPU", "GPU", 2);
	gpuList.emplace_back("Level 3 GPU", "GPU", 3);

	ramList.emplace_back("Level 1 DDR3 RAM", RamSocketType::DDR3, "RAM", 1);
	ramList.emplace_back("Level 2 DDR4 RAM", RamSocketType::DDR4, "RAM", 2);
	ramList.emplace_back("Level 3 DDR4 RAM", RamSocketType::DDR4, "RAM", 3);

	psuList.emplace_back("Level 1 PSU", "PSU", 1);
	psuList.emplace_back("Level 2 PSU", "PSU", 2);
	psuList.emplace_back("Level 3 PSU", "PSU", 3);

	pcCaseList.emplace_back("Level 1 PC Case", "Case", 1);
	pcCaseList.emplace_back("Level 2 PC Case", "Case", 2);
	pcCaseList.emplace_back("Level 3 PC Case", "Case", 3);

	ssdList.emplace_back("Level 1 SSD", "SSD", 1);
	ssdList.emplace_back("Level 2 SSD", "SSD", 2);
	ssdList.emplace_back("Level 3 SSD", "SSD", 3);

	hddList.emplace_back("Level 1 HDD", "HDD", 1);
	hddList.emplace_back("Level 2 HDD", "HDD", 2);
	hddList.emplace_back("Level 3 HDD", "HDD", 3);
}

void GuiManager::Draw()
{
	//Clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ImGUI refresh
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Decide which screen needs to be drawn and draw
	if (showMenuScreen)
		DrawMenuScreen();
	else if (showTutorialScreen)
		DrawTutorialScreen();
	else if (showPcBuilderScreen)
		DrawPcBuilderScreen();

	//Draw all components
	controller.HandleDraw(window);

	//ImGUI finish render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::DrawMenuScreen()
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

	if (ImGui::Button("PC Builder", ImVec2(150, 50)))
	{
		showMenuScreen = false;
		showTutorialScreen = false;
		showPcBuilderScreen = true;
		controller.SetCinematicMode(false);
		controller.SetIsDrawing(true);
	}
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 150.0f) * 0.5f);

	// if (ImGui::Button("Tutorial", ImVec2(150, 50)))
	// {
	// 	showMenuScreen = false;
	// 	showTutorialScreen = true;
	// 	showPcBuilderScreen = false;
	// 	controller.SetIsDrawing(false);
	// }

	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 100.0f) * 0.5f);

	if (ImGui::Button("Exit", ImVec2(100, 30)))
	{
		glfwSetWindowShouldClose(window, true);
	}

	ImGui::End();
}

void GuiManager::DrawTutorialScreen()
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

void GuiManager::DrawPcBuilderScreen()
{
	if (isBuildMode)
	{
		ImGui::Begin("PC Builder");

		DrawPartSelectionList();

		DrawBuilderTopRight();

		DrawChosenPcPartsList();

		DrawCompatibilityInterface();

		ImGui::End();
	}
	else if (isCinematicMode)
	{
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Cinematic View", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		DrawCinematicViewControls();

		DrawBuilderTopRight();
		ImGui::End();
	}
}

void GuiManager::DrawCinematicViewControls()
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
	// rotation buttons
	ImGui::SetCursorPos(ImVec2(padding, padding));
	while (ImGui::Button("Left", buttonSize))
		controller.ChangePosition(glm::vec3(-0.5, 0, 0));
	ImGui::SetCursorPos(ImVec2(padding + buttonSize.x + padding, padding));
	while (ImGui::Button("Right", buttonSize))
		controller.ChangePosition(glm::vec3(0.5, 0, 0));

	ImGui::SetCursorPos(ImVec2(padding, padding + (buttonSize.y + padding)));
	while (ImGui::Button("Up", buttonSize))
		controller.ChangePosition(glm::vec3(0, 0.5, 0));

	ImGui::SetCursorPos(ImVec2(padding + (buttonSize.x + padding), padding + (buttonSize.y + padding)));
	while (ImGui::Button("Down", buttonSize))
		controller.ChangePosition(glm::vec3(0, -0.5, 0));

	ImGui::SetCursorPos(ImVec2(padding, padding + ((buttonSize.y + padding) * 2)));
	while (ImGui::Button("Forward", buttonSize))
		controller.ChangePosition(glm::vec3(0, 0, 0.5));

	ImGui::SetCursorPos(ImVec2(padding + (buttonSize.x + padding), padding + ((buttonSize.y + padding) * 2)));
	while (ImGui::Button("backward", buttonSize))
		controller.ChangePosition(glm::vec3(0, 0, -0.5));

	// translation buttons
	ImGui::SetCursorPos(ImVec2(windowSize.x - ((buttonSize.x + padding) * 2), padding));
	while (ImGui::Button("Rotate Y left", buttonSize))
		controller.ChangeRotationY(-24);

	ImGui::SetCursorPos(ImVec2(windowSize.x - padding - buttonSize.x, padding));
	while (ImGui::Button("Rotate Y right", buttonSize))
		controller.ChangeRotationY(24);

	ImGui::SetCursorPos(ImVec2(windowSize.x - ((buttonSize.x + padding) * 2), padding + (buttonSize.y + padding)));
	while (ImGui::Button("Rotate X up", buttonSize))
		controller.ChangeRotationX(24);

	ImGui::SetCursorPos(ImVec2(windowSize.x - padding - buttonSize.x, padding + (buttonSize.y + padding)));
	while (ImGui::Button("Rotate X down", buttonSize))
		controller.ChangeRotationX(-24);

	ImGui::SetCursorPos(ImVec2(windowSize.x - ((buttonSize.x + padding) * 2),
	                           padding + ((buttonSize.y + padding) * 2)));
	while (ImGui::Button("Rotate Z forward", buttonSize))
		controller.ChangeRotationZ(-24);

	ImGui::SetCursorPos(ImVec2(windowSize.x - padding - buttonSize.x, padding + ((buttonSize.y + padding) * 2)));
	while (ImGui::Button("Rotate Z backward", buttonSize))
		controller.ChangeRotationZ(24);
	//reset button
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f)); // Set button color to red
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f));
	// Set button hover color to a lighter red
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 1.0f));
	// Set button active color to a darker red

	ImGui::SetCursorPos(ImVec2(windowSize.x / 2, windowSize.y - padding - buttonSize.x));
	while (ImGui::Button("Reset", buttonSize))
	{
		controller.ResetRotation();
		controller.ResetTranslation();
	}

	// Restore the original style
	style.Colors[ImGuiCol_Button] = originalButtonColor;
	style.Colors[ImGuiCol_ButtonHovered] = originalButtonHoveredColor;
	style.Colors[ImGuiCol_ButtonActive] = originalButtonActiveColor;
	style.Colors[ImGuiCol_Text] = originalTextColor;

	ImGui::End();
}

void GuiManager::DrawCompatibilityInterface()
{
	if (ImGui::Button("Show Compatibility Tips", ImVec2(ImGui::GetItemRectSize().x, 60.0f)))
	{
		if (showCompatibility)
		{
			showCompatibility = false;
		}
		else
		{
			showCompatibility = true;
		}
	}
	if (showCompatibility)
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

void GuiManager::DrawPartSelectionList()
{
	//Top left window
	ImGui::Begin("Components chooser", nullptr, ImGuiWindowFlags_NoTitleBar);

	ImGui::Text("Processors");
	DrawPartList(cpuList, CPU_TYPE);

	ImGui::Text("Cpu coolers");
	DrawPartList(fanList, FAN_TYPE);

	ImGui::Text("Memory modules");
	DrawPartList(ramList, RAM_TYPE);

	ImGui::Text("Graphics cards");
	DrawPartList(gpuList, GPU_TYPE);

	ImGui::Text("Mother boards");
	DrawPartList(mbuList, MBU_TYPE);

	ImGui::Text("Power supplies");
	DrawPartList(psuList, PSU_TYPE);

	ImGui::Text("Pc cases");
	DrawPartList(pcCaseList, PC_CASE_TYPE);

	ImGui::Text("SSD");
	DrawPartList(ssdList, SSD_TYPE);

	ImGui::Text("HDD");
	DrawPartList(hddList, HDD_TYPE);

	DrawAddPartButton();

	ImGui::End();
}

void GuiManager::DrawBuilderTopRight()
{
	//Top right window
	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 400.0f, 0.0f));
	ImGui::Begin("Navigation Buttons", nullptr, ImGuiWindowFlags_NoTitleBar);

	if (ImGui::Button("Build Mode", ImVec2(ImGui::GetItemRectSize().x, 40.0f)))
	{
		isBuildMode = true;
		isCinematicMode = false;
		controller.SetCinematicMode(false);
	}

	if (ImGui::Button("Cinematic Mode", ImVec2(ImGui::GetItemRectSize().x, 40.0f)))
	{
		isCinematicMode = true;
		isBuildMode = false;
		controller.SetCinematicMode(true);
	}


	if (ImGui::Button("Show pc", ImVec2(ImGui::GetItemRectSize().x, 40.0f)))
	{
		SetPcObjects();
	}
	if (ImGui::Button("Hide pc", ImVec2(ImGui::GetItemRectSize().x, 40.0f)))
	{
		ClearPcObjects();
	}
}

void GuiManager::DrawChosenPcPartsList()
{
	ImGui::Text("Chosen Pc parts");

	for (int n = 0; n < pcParts.size(); n++)
	{
		ImGui::PushID(n);
		if (ImGui::Button(pcParts[n]->GetName().c_str(), ImVec2(250, 40)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", pcParts[n]->GetName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
	}

	DrawDeletePartButton();
}

void GuiManager::SetPcObjects()
{
	ClearPcObjects();
	for (const PcPart* part : pcParts)
	{
		std::string objectPath = part->GetObjectPath();
		controller.objects.emplace_back(directory, objectPath, part->GetTier());
	}
}

void GuiManager::ClearPcObjects()
{
	controller.objects.clear();
}

void GuiManager::DrawAddPartButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.8f, 0.2f, 1.0f)); // Set button color to green
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.9f, 0.3f, 1.0f));
	// Set button hover color to a lighter green
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.7f, 0.1f, 1.0f));
	// Set button active color to a darker green

	ImGui::Button("Add PC Part", ImVec2(335, 230));

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
			SetPcObjects();
		}
		ImGui::EndDragDropTarget();
	}
}

void GuiManager::DrawDeletePartButton()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f)); // Set button color to red
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f));
	// Set button hover color to a lighter red
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 1.0f));
	// Set button active color to a darker red

	if (ImGui::Button("Delete Part", ImVec2(250, 70)))
	{
	}

	ImGui::PopStyleColor(3);

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(int));
			int payload_n = *(const int*)payload->Data;
			std::string partName = pcParts[payload_n]->GetName().c_str();
			for (CPU& cpu : cpuList)
			{
				if (cpu.GetName() == partName)
				{
					pickedCPU = nullptr; // Set pickedCPU to nullptr
					break;
				}
			}

			for (Fan& fan : fanList)
			{
				if (fan.GetName() == partName)
				{
					pickedFan = nullptr; // Set pickedFan to nullptr
					break;
				}
			}

			for (RAM& ram : ramList)
			{
				if (ram.GetName() == partName)
				{
					pickedRAM = nullptr; // Set pickedRAM to nullptr
					break;
				}
			}

			for (GPU& gpu : gpuList)
			{
				if (gpu.GetName() == partName)
				{
					pickedGPU = nullptr; // Set pickedGPU to nullptr
					break;
				}
			}

			for (Motherboard& mbu : mbuList)
			{
				if (mbu.GetName() == partName)
				{
					pickedMotherboard = nullptr; // Set pickedMotherboard to nullptr
					break;
				}
			}

			for (PSU& psu : psuList)
			{
				if (psu.GetName() == partName)
				{
					pickedPSU = nullptr; // Set pickedPSU to nullptr
					break;
				}
			}

			for (PcCase& pcCase : pcCaseList)
			{
				if (pcCase.GetName() == partName)
				{
					pickedCase = nullptr; // Set pickedCase to nullptr
					break;
				}
			}

			for (Storage& ssd : ssdList)
			{
				if (ssd.GetName() == partName)
				{
					pickedSSD = nullptr; // Set pickedStorage to nullptr
					break;
				}
			}
			for (Storage& hdd : hddList)
			{
				if (hdd.GetName() == partName)
				{
					pickedHDD = nullptr; // Set pickedStorage to nullptr
					break;
				}
			}
			// Delete the dragged part from the pcParts vector
			pcParts.erase(pcParts.begin() + payload_n);
			SetPcObjects();
		}

		ImGui::EndDragDropTarget();
	}
}

template <typename T>
void GuiManager::DrawPartList(const std::vector<T>& partsList, int part)
{
	for (int n = 0; n < partsList.size(); n++)
	{
		ImGui::PushID(n);
		if (ImGui::Button(partsList[n].GetName().c_str(), ImVec2(110, 65)));

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			partType = part;
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));
			ImGui::Text("Copy %s", partsList[n].GetName().c_str());
			ImGui::EndDragDropSource();
		}

		ImGui::PopID();
		if (n + 1 < partsList.size())
		{
			ImGui::SameLine();
		}
	}
}
