#pragma once
#include "GenesisClient/Defines.hpp"

#define GLFW_INCLUDE_NONE
#include "GenesisClient/Window.hpp"
#include "GenesisClient/platform/opengl/OpenGLContext.hpp"

#include <GLFW/glfw3.h>

namespace ge {
	namespace client {
		struct WindowData {
		public:
			String title;
			uint32 width, height;
			bool vSync, cursorGrabbed;
			IWindow::EventCallback eventFunc;
		};

		class WindowsWindow: public IWindow {
		public:
			static IWindow* create(const WindowConfiguration& props = WindowConfiguration());

			WindowsWindow(const WindowConfiguration& props);
			~WindowsWindow();

			void init(const WindowConfiguration& props);
			void shutdown();

			void onUpdate() override;
			inline uint32 getWidth() const override;
			inline uint32 getHeight() const override;
			inline float32 getWidthF() const override;
			inline float32 getHeightF() const override;

			void setEventCallback(const EventCallback& func) override;

			void setVSync(bool enable) override;
			bool isVSync() const override { return data.vSync; }
			void setCursorGrabbed(bool grabbed) override;
			bool isCursorGrabbed() const override { return data.cursorGrabbed; }

			bool shouldClose() const override { return glfwWindowShouldClose(handle); }

			void* getNativeWindow() const override { return handle; }

		private:
			WindowData data;
			GLFWwindow* handle;
			OpenGLContext* context;

			static uint8 glfwWindowCount;
			bool cursorGrabbed;
		};
	}
}
