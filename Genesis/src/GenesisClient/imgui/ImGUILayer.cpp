#include "ImGUILayer.hpp"

#include <GLFW/glfw3.h>
#include <GenesisClient/Application.hpp>
#include <GenesisCore/Logger.hpp>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#define GE_GetImGuiIO() ImGuiIO& io = ImGui::GetIO();

namespace ge {
	namespace client {
		void ImGUILayer::onAttach() {
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			GE_GetImGuiIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui::StyleColorsDark();

			float32 fontSize = 24.f; // *2
			io.Fonts->AddFontFromFileTTF("fonts/roboto/Roboto-Bold.ttf", fontSize);
			io.FontDefault = io.Fonts->AddFontFromFileTTF("fonts/roboto/Roboto-Regular.ttf", fontSize);

			ImGuiStyle& style = ImGui::GetStyle();
			if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				style.WindowRounding = 0.f;
				style.Colors[ImGuiCol_WindowBg].w = 1.f;
			}

			Application& app = Application::getInstance();
			GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 410");
		}
		void ImGUILayer::onDetach() {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void ImGUILayer::begin() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		void ImGUILayer::end() {
			GE_GetImGuiIO();
			Application& app = Application::getInstance();
			io.DisplaySize = ImVec2(static_cast<float32>(app.getWindow().getWidth()), static_cast<float32>(app.getWindow().getHeight()));

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backupCurrentContext);
			}
		}
	}
}
