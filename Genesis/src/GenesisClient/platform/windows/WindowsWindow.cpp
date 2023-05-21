#include "GenesisClient/platform/windows/WindowsWindow.hpp"

#include "GenesisClient/renderer/GraphicsContext.hpp"

#include <GenesisCore/Logger.hpp>
#include <GenesisCore/event/Event.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <GenesisCore/event/MouseEvent.hpp>
#include <GenesisCore/event/WindowEvent.hpp>
#include <glad/glad.h>

#define GE_GetWindowData() WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window)

namespace ge {
	namespace client {
		uint8 WindowsWindow::glfwWindowCount = 0;

		static void GLFWErrorCallback(int error, const char* description) { GE_Fatal("GLFWError ({0}): {1}", error, description); }

		WindowsWindow::WindowsWindow(const WindowConfiguration& props) { init(props); }
		WindowsWindow::~WindowsWindow() { shutdown(); }

		void WindowsWindow::init(const WindowConfiguration& props) {
			// Set Window Props
			data.title = props.title;
			data.width = props.width;
			data.height = props.height;

			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_DECORATED, true);
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);
			glfwWindowHint(GLFW_ALPHA_BITS, 8);
			glfwWindowHint(GLFW_RED_BITS, 8);
			glfwWindowHint(GLFW_GREEN_BITS, 8);
			glfwWindowHint(GLFW_BLUE_BITS, 8);

			// Create Window
			GE_Info("Creating Window '{0}'...", data.title);
			if(glfwWindowCount == 0) {
				// If first window, initialize GLFW
				GE_Info("Initializing GLFW...");
				int success = glfwInit();
				if(!success) {
					GE_Fatal("Could not initialize GLFW!");
				}

				GE_Info("Initializing GLFW error callback...");
				glfwSetErrorCallback(GLFWErrorCallback);
			}

// If not in distribution, enable opengl debug logs
#ifndef GE_DIST
// glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

			// Now create the window and create the context
			// Context will later be abstracted to support also directx and vulkan context
			handle = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
			context = (OpenGLContext*) IGraphicsContext::create(handle);
			context->init();

			setVSync(true);
			glfwSetWindowUserPointer(handle, &data);

			++glfwWindowCount;

			// Set GLFW Callbacks
			glfwSetWindowSizeCallback(handle, [](GLFWwindow* window, int32 width, int32 height) {
				GE_GetWindowData();
				data.width = width;
				data.height = height;

				ge::core::WindowResizeEvent e(width, height);
				data.eventFunc(e);
			});
			glfwSetWindowCloseCallback(handle, [](GLFWwindow* window) {
				GE_GetWindowData();

				ge::core::WindowCloseEvent e;
				data.eventFunc(e);
			});
			glfwSetKeyCallback(handle, [](GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods) {
				GE_GetWindowData();

				switch(action) {
					case GLFW_PRESS: {
						ge::core::KeyDownEvent e(key, 0);
						data.eventFunc(e);
						break;
					}
					case GLFW_RELEASE: {
						ge::core::KeyUpEvent e(key);
						data.eventFunc(e);
						break;
					}
					case GLFW_REPEAT: {
						ge::core::KeyDownEvent e(key, true);
						data.eventFunc(e);
						break;
					}
				}
			});
			glfwSetCharCallback(handle, [](GLFWwindow* window, uint32 keycode) {
				GE_GetWindowData();

				ge::core::KeyTypedEvent e(keycode);
				data.eventFunc(e);
			});
			glfwSetMouseButtonCallback(handle, [](GLFWwindow* window, int32 button, int32 action, int32 mods) {
				GE_GetWindowData();

				switch(action) {
					case GLFW_PRESS: {
						ge::core::MouseButtonDownEvent e(button);
						data.eventFunc(e);
						break;
					}
					case GLFW_RELEASE: {
						ge::core::MouseButtonUpEvent e(button);
						data.eventFunc(e);
						break;
					}
				}
			});
			glfwSetScrollCallback(handle, [](GLFWwindow* window, float64 x, float64 y) {
				GE_GetWindowData();

				ge::core::MouseScrolledEvent e(static_cast<float32>(x), static_cast<float32>(y));
				data.eventFunc(e);
			});
			glfwSetCursorPosCallback(handle, [](GLFWwindow* window, float64 x, float64 y) {
				GE_GetWindowData();

				ge::core::MouseMovedEvent e(static_cast<float32>(x), static_cast<float32>(y));
				data.eventFunc(e);
			});
		}

		void WindowsWindow::onUpdate() {
			glfwPollEvents();
			context->swapBuffers();
		}
		uint32 WindowsWindow::getWidth() const { return data.width; }
		uint32 WindowsWindow::getHeight() const { return data.height; }

		float32 WindowsWindow::getWidthF() const { return static_cast<float32>(data.width); }
		float32 WindowsWindow::getHeightF() const { return static_cast<float32>(data.height); }

		void WindowsWindow::setEventCallback(const EventCallback& func) { data.eventFunc = func; }
		void WindowsWindow::setVSync(bool enable) {
			data.vSync = enable;
			glfwSwapInterval(data.vSync ? 1 : 0);
		}
		void WindowsWindow::setCursorGrabbed(bool grabbed) {
			data.cursorGrabbed = grabbed;
			glfwSetInputMode(handle, GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		}

		void WindowsWindow::shutdown() {
			glfwWindowCount--;
			std::cout << "Destroying '" << data.title << "'..." << std::endl;
			glfwDestroyWindow(handle);
			--glfwWindowCount;

			if(glfwWindowCount == 0) glfwTerminate();

			delete context;
		}
	}
}
