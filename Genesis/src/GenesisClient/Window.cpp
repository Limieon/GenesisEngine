#include "Window.hpp"

#ifdef GE_PLATFORM_WINDOWS
#	include "GenesisClient/platform/windows/WindowsWindow.hpp"
#else
#	error Undefined Plattform! Currently only Windows is supported!
#endif

namespace ge {
	namespace client {
		IWindow* IWindow::create(const WindowConfiguration& props) {
#ifdef GE_PLATFORM_WINDOWS
			return new WindowsWindow(props);
#endif
			return nullptr;
		}
	}
}
