#include "Application.hpp"

#include "Platform.hpp"
#include "renderer/Buffer.hpp"
#include "renderer/RenderCommand.hpp"
#include "renderer/RendererAPI.hpp"
#include "renderer/Shader.hpp"
#include "renderer/VertexArray.hpp"

#include <GenesisCore/Logger.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <iostream>

namespace ge {
	namespace client {
		Application* Application::instance = nullptr;

		Application::Application(const ApplicationConfiguration& appConfig, const WindowConfiguration& windConfig) {
			ge::core::Logger::init();

			GE_Assert(!instance, "There can only be one application instance!");

			instance = this;

			GE_Info("Intializing Engine Components...");
			window = IWindow::create(windConfig);
			window->setEventCallback(GE_BindEventFunction(Application::onEvent));
			window->setVSync(true);

			imGuiLayer = new ImGUILayer();
			layerStack.pushOverlay(imGuiLayer);
		}
		Application::~Application() { delete window; }

		void Application::onEvent(ge::core::Event& e) {
			ge::core::EventDispatcher dispatcher(e);

			// Dispatch event directly to internal functions
			dispatcher.dispatch<ge::core::WindowCloseEvent>(GE_BindEventFunction(Application::onWindowClose));
			dispatcher.dispatch<ge::core::WindowResizeEvent>(GE_BindEventFunction(Application::onWindowResize));

			// Go through layers until event has been handled
			for(auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
				if(e.isHandled()) break;
				(*it)->onEvent(e);
			}
		}

		bool Application::onWindowClose(ge::core::WindowCloseEvent& e) {
			running = false;
			return true;
		}
		bool Application::onWindowResize(ge::core::WindowResizeEvent& e) {
			if(e.getWidth() == 0 || e.getHeight() == 0) {
				minimized = true;
				return false;
			}

			minimized = false;
			RenderCommand::setViewport(0, 0, e.getWidth(), e.getHeight());

			return false;
		}

		void Application::run() {
			GE_Info("Starting application...");

			float32 time;
			RenderCommand::setClearColor({0.f, 0.f, 0.f, 1.f});
			while(running) {
				time = Platform::getTime();
				ge::core::Timestep timestep = time - lastTime;
				lastTime = time;

				if(!minimized) {
					for(ge::core::Layer* layer: layerStack) {
						layer->onUpdate(timestep);
					}
				}

				{
					imGuiLayer->begin();
					for(ge::core::Layer* layer: layerStack) {
						layer->onImGUIRender();
					}
					imGuiLayer->end();
				}

				window->onUpdate();
			}

			ge::core::Logger::release();
		}
	}
}
