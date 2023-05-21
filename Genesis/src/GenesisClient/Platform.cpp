#include "Platform.hpp"

#ifdef GE_PLATFORM_WINDOWS
#	include "GenesisClient/platform/windows/WindowsPlatform.hpp"
#endif

namespace ge {
	namespace client {
#ifdef GE_PLATFORM_WINDOWS
		Platform* Platform::instance = new WindowsPlatform();
#else
#	error Currenlty, only windows is supported!
#endif
	}
}
