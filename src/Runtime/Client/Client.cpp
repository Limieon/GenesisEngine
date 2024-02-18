#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Genesis/Client/Client.hpp>
#include <Genesis/Core/Core.hpp>
#include <Genesis/Server/Server.hpp>
#include <Runtime/Common/Common.hpp>
#include <bgfx/bgfx.h>
#include <imgui.h>
#include <iostream>

uint16_t width = 1920;
uint16_t height = 1080;

GLFWwindow* window;

int main(int argc, char** argv) {
	std::cout << "Starting Client..." << std::endl;

	ge::core::Core::init();
	rt::common::Common::init();
	ge::server::Server::init();
	ge::client::Client::init();

	glfwInit();
	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

	window = glfwCreateWindow(width, height, "GenesisEngine", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	bgfx::Init init;
	init.type = bgfx::RendererType::OpenGL;
	init.vendorId = BGFX_PCI_ID_NVIDIA;
	init.platformData.nwh = glfwGetWin32Window(window);
	init.resolution.width = width;
	init.resolution.height = height;

	bgfx::init(init);
	bgfx::setDebug(BGFX_DEBUG_STATS | BGFX_DEBUG_TEXT);
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

	while(!glfwWindowShouldClose(window)) {
		bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
		bgfx::touch(0);
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x0f,
		                    "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

		bgfx::dbgTextPrintf(80, 1, 0x0f,
		                    "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
		bgfx::dbgTextPrintf(80, 2, 0x0f,
		                    "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

		bgfx::frame();
		glfwPollEvents();
	}

	bgfx::shutdown();
}
