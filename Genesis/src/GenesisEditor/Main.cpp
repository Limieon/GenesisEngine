#include <GenesisCore/Genesis.hpp>

int main(int argc, char** argv) {
	ge::core::Logger::init();
	GE_Info("Starting Editor...");

	std::cin.get();

	return 0;
}
