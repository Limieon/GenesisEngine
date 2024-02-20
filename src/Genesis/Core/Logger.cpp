#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace ge {
	namespace core {
		Ref<spdlog::logger> Logger::handle;

		void Logger::init() {
			spdlog::set_pattern("<%T>[%^%l%$/%s:%#] %v");
			handle = spdlog::stdout_color_mt("Genesis");
			handle->set_level(spdlog::level::trace);
		}
		void Logger::release() {}
	}
}
