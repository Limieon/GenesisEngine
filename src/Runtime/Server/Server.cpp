#include <Genesis/Server/Server.hpp>
#include <Runtime/Common/Common.hpp>
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Starting Server..." << std::endl;

	rt::common::Common::init();
	ge::server::Server::init();

	std::cin.get();
}
