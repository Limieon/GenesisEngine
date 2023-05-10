#include <GenesisClient/Application.hpp>
#include <GenesisClient/Entry.hpp>

#include <GenesisCore/Genesis.hpp>

#include <iostream>

class RuntimeClient: public ge::client::Application {
public:
	RuntimeClient() {
		ge::core::Logger::init();
		GE_Info("Hello World!");
		std::cin.get();
		ge::core::Logger::release();
	}
	~RuntimeClient() {
	}
};

ge::client::Application* ge::client::createApplication() {
	return new RuntimeClient();
}
