#include "GUIManager.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GUIManager
{
public:
	GLFWwindow* window;


	void initImGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}
};
