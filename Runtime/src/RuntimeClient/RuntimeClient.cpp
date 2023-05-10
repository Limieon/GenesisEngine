#include <GenesisClient/Application.hpp>
#include <GenesisClient/Entry.hpp>

#include <iostream>

class RuntimeClient: public ge::client::Application {
public:
	RuntimeClient() {
		std::cout << "Hello Client!" << std::endl;
		std::cin.get();
	}
	~RuntimeClient() {
	}
};

ge::client::Application* ge::client::createApplication() {
	return new RuntimeClient();
}
