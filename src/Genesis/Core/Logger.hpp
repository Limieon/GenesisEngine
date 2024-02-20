#pragma once
#include "Defines.hpp"

#include <spdlog/spdlog.h>

namespace ge {
	namespace core {
		class Logger {
		public:
			static void init();
			static void release();

			inline static Ref<spdlog::logger> getLogger() { return handle; }

		private:
			static Ref<spdlog::logger> handle;
		};
	}
}

#ifndef GE_CONFIG_DIST
#	define GE_Info(...) SPDLOG_INFO(__VA_ARGS__)
#	define GE_Warn(...) SPDLOG_WARN(__VA_ARGS__)
#	define GE_Error(...) SPDLOG_ERROR(__VA_ARGS__)
#	define GE_Fatal(...) SPDLOG_CRITICAL(__VA_ARGS__)
#else
#	define GE_Info(...) SPDLOG_INFO(__VA_ARGS__)
#	define GE_Warn(...) SPDLOG_WARN(__VA_ARGS__)
#	define GE_Error(...) SPDLOG_ERROR(__VA_ARGS__)
#	define GE_Fatal(...) SPDLOG_CRITICAL(__VA_ARGS__)
#endif

#ifndef GE_CONFIG_DIST
#	define GE_Assert(x, ...)                                                                                                                        \
		{                                                                                                                                            \
			if(!(x)) {                                                                                                                               \
				GE_Fatal("Assertion Triggered:");                                                                                                    \
				GE_Fatal(__VA_ARGS__);                                                                                                               \
				__debugbreak();                                                                                                                      \
			}                                                                                                                                        \
		}
#else
#	define GE_Assert(x, ...)
#endif
