#pragma once
#include "Event.hpp"

namespace ge {
	namespace core {
		class WindowEvent: public Event {
		public:
			WindowEvent() {}
			EVENT_CLASS_CATEGORY(EventCategoryWindow)
		};

		class WindowCloseEvent: public WindowEvent {
		public:
			WindowCloseEvent() {}

			EVENT_CLASS_TYPE(WindowClose)
		};
		class WindowFocusEvent: public WindowEvent {
		public:
			WindowFocusEvent() {}

			EVENT_CLASS_TYPE(WindowFocus)
		};
		class WindowFocusLostEvent: public WindowEvent {
		public:
			WindowFocusLostEvent() {}

			EVENT_CLASS_TYPE(WindowFocusLost)
		};

		class WindowMovedEvent: public Event {
		public:
			WindowMovedEvent(uint32 x, uint32 y): x(x), y(y) {}

			inline uint32 getX() { return x; }
			inline uint32 getY() { return y; }

			EVENT_CLASS_CATEGORY(EventCategoryWindow)
			EVENT_CLASS_TYPE(WindowMoved)
		private:
			uint32 x, y;
		};

		class WindowResizeEvent: public Event {
		public:
			WindowResizeEvent(uint32 width, uint32 height): width(width), height(height) {}

			inline uint32 getWidth() { return width; }
			inline uint32 getHeight() { return height; }

			EVENT_CLASS_CATEGORY(EventCategoryWindow)
			EVENT_CLASS_TYPE(WindowMoved)
		private:
			uint32 width, height;
		};
	}
}
