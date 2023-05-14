#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <vulkan/vulkan.h>

#include <GenesisCore/Defines.hpp>
#include <GenesisCore/Genesis.hpp>

int main(int argc, char** argv) {
	ge::core::Logger::init();

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Genesis Engine", 0, 0);

	uint32 extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	GE_Info("{} extensions supported!", extensionCount);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return true;
}
