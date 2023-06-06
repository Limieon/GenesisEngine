#include "ClientLayer.hpp"
#include "ClientLayer2D.hpp"

#include <GenesisClient/Entry.hpp>
#include <GenesisClient/Genesis.hpp>

class RuntimeClient: public ge::client::Application {
public:
	RuntimeClient(const ge::client::ApplicationConfiguration& appConfig, const ge::client::WindowConfiguration& windConfig)
	    : Application(appConfig, windConfig) {
		pushLayer(new runtime::ClientLayer());
	}
	~RuntimeClient() {}
};

ge::client::Application* ge::client::createApplication() {
	ApplicationConfiguration appConfig;
	appConfig.name = "Genesis Application";

	WindowConfiguration windConfig;
	windConfig.title = "Genesis Application - Client";
	windConfig.width = 1920;
	windConfig.height = 1080;

	return new RuntimeClient(appConfig, windConfig);
}
