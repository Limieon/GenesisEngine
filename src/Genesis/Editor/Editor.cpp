#include <Genesis/Client/Client.hpp>
#include <Genesis/Server/Server.hpp>
#include <Runtime/Common/Common.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Editor..." << std::endl;

	ge::server::Server::init();
	ge::client::Client::init();
	rt::common::Common::init();

	std::cin.get();
}
