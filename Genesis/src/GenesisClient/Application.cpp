#include "Application.hpp"

#include "renderer/Buffer.hpp"
#include "renderer/RenderCommand.hpp"
#include "renderer/RendererAPI.hpp"
#include "renderer/Shader.hpp"
#include "renderer/VertexArray.hpp"

#include <GenesisCore/Logger.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <iostream>

struct Vertex {
	glm::vec3 pos;
	glm::vec4 color;
};

namespace ge {
	namespace client {
		Application* Application::instance = nullptr;

		Application::Application(const ApplicationConfiguration& appConfig, const WindowConfiguration& windConfig) {
			ge::core::Logger::init();

			GE_Info("Intializing Engine Components...");
			window = IWindow::create(windConfig);
			window->setEventCallback(GE_BindEventFunction(Application::onEvent));
			window->setVSync(true);
		}
		Application::~Application() { delete window; }

		void Application::onEvent(ge::core::Event& e) {
			if(e.getEventType() == ge::core::EventType::KeyDown) {
				auto keyEvent = (ge::core::KeyTypedEvent&) e;
				GE_Info("Key Down Event Fired: {}", keyEvent.getKeyCode());
				return;
			}

			GE_Info("Event Fired: {}", e.getName());
		}

		void Application::run() {
			GE_Info("Starting application...");

			std::vector<Vertex> vertices;
			vertices.push_back({{-.5f, -.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}});
			vertices.push_back({{.5f, -.5f, 0.f}, {0.f, 1.f, 0.f, 1.f}});
			vertices.push_back({{0.f, .5f, 0.f}, {0.f, 0.f, 1.f, 1.f}});

			uint32 indices[] = {0, 1, 2};

			GE_Info("{} {}", sizeof(vertices), sizeof(Vertex));

			Ref<IVertexBuffer> vb = IVertexBuffer::create(vertices.data(), 3 * sizeof(Vertex));
			vb->bind();
			vb->setLayout({{ShaderDataType::FLOAT3, "a_pos"}, {ShaderDataType::FLOAT4, "a_color"}});

			Ref<IIndexBuffer> ib = IIndexBuffer::create(indices, 3);
			ib->bind();

			Ref<IVertexArray> va = IVertexArray::create();
			va->addVertexBuffer(vb);
			va->setIndexBuffer(ib);

			Ref<IShader> shader = IShader::create("shaders/basic.glsl");
			shader->bind();

			RenderCommand::setClearColor({0.f, 0.f, 0.f, 1.f});
			while(running) {
				RenderCommand::clear();

				RenderCommand::drawIndexed(va, 3);

				window->onUpdate();
			}

			ge::core::Logger::release();
		}
	}
}
