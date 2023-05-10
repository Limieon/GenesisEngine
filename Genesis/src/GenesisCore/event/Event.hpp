#pragma once
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace core {
		enum class EventType {
			None = 0,
			WindowClose,
			WindowResize,
			WindowFocus,
			WindowFocusLost,
			WindowMoved,
			KeyDown,
			KeyUp,
			KeyTyped,
			MouseButtonDown,
			MouseButtonUp,
			MouseMoved,
			MouseScrolled
		};
		enum EventCategory {
			None = 0,
			EventCategoryWindow = GE_BIT(0),
			EventCategoryInput = GE_BIT(1),
			EventCategoryKeyboard = GE_BIT(2),
			EventCategoryMouse = GE_BIT(3)
		};

#define EVENT_CLASS_TYPE(type)                                                  \
	static EventType getStaticType() { return EventType::##type; }              \
	virtual EventType getEventType() const override { return getStaticType(); } \
	virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int32 getCategoryFlags() const override { return category; }

		class Event {
			friend class EventDispatcher;

		public:
			virtual EventType getEventType() const = 0;
			virtual const char* getName() const = 0;
			virtual int32 getCategoryFlags() const = 0;

			inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }

			inline bool isHandled() { return handled; }

		protected:
			bool handled = false;
		};

		class EventDispatcher {
			template <typename T>
			using EventFunc = std::function<bool(T&)>;

		public:
			EventDispatcher(Event& e): e(e) {}

			template <typename T>
			bool dispatch(EventFunc<T> func) {
				if(e.getEventType() == T::getStaticType()) {
					e.handled = func(*(T*) &e);
					return true;
				}
				return false;
			}

		private:
			Event& e;
		};
	}
}
