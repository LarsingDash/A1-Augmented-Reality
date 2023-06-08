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
static const char* list1[9] =
{
	"CPU1", "CPU2", "CPU3","CPU4", "CPU5", "CPU6","CPU7", "CPU8", "CPU9"
};
static const char* list2[9] =
{
	"Select a part", "Select a part", "Select a part","Select a part", "Select a part", "Select a part","Select a part", "Select a part", "Select a part"
};
void GUIManager::drawPCBuilderScreen()
{
	if (ImGui::TreeNode("Drag and drop to copy/swap items"))
	{
		
	
		for (int n = 0; n < IM_ARRAYSIZE(list1); n++)
		{
			ImGui::PushID(n);

			ImGui::Button(list1[n], ImVec2(70, 20));

			// Our buttons are both drag sources and drag targets here!
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				// Set payload to carry the index of our item (could be anything)
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));

				// Display preview (could be anything, e.g. when dragging an image we could decide to display
				// the filename and a small preview of the image, etc.)
				if (mode == Mode_Copy) { ImGui::Text("Copy %s", list1[n]); }
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
						list1[n] = list1[payload_n];
					}
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::PopID();
		}
		for (int m = 0; m < IM_ARRAYSIZE(list1); m++)
		{
			ImGui::PushID(m);

			ImGui::Button(list2[m], ImVec2(150, 20));

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &m, sizeof(int));

				
				if (mode == Mode_Copy) { ImGui::Text("Copy %s", list2[m]); }
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
						list2[m] = list1[payload_m];
					}
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::PopID();
		}
		ImGui::TreePop();
	}

}
