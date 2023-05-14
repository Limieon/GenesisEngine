#include <GenesisClient/Application.hpp>
#include <GenesisClient/Entry.hpp>

#include <GenesisCore/Genesis.hpp>

#include <iostream>

class RuntimeClient: public ge::client::Application {
public:
	RuntimeClient() {
		ge::core::Logger::init();
		ge::core::Event* e = new ge::core::KeyDownEvent(ge::Key::E, 7);

		GE_Info("Hello World!");
		GE_Info("Event: {}, Key: {}, Count: {}", e->getName(), ((ge::core::KeyDownEvent*) e)->getKeyCode(), ((ge::core::KeyDownEvent*) e)->getRepeatCount());

		std::cin.get();
		ge::core::Logger::release();
	}
	~RuntimeClient() {
	}
};

ge::client::Application* ge::client::createApplication() {
	return new RuntimeClient();
}
