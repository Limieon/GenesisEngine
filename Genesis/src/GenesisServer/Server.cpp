#include "Server.hpp"

#include "registry/GameRegistry.hpp"

namespace ge {
	namespace server {
		void Server::init() { GameRegistry::init(); }
		void Server::release() { GameRegistry::release(); }
	}
}
