#pragma once
#include "GenesisCore/KeyCode.hpp"
#include "GenesisCore/event/Event.hpp"

namespace ge {
	namespace core {
		class KeyEvent: public Event {
		public:
			inline KeyCode getKeyCode() const { return keyCode; }

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

		protected:
			KeyEvent(KeyCode keyCode): keyCode(keyCode) {}
			KeyCode keyCode;
		};

		class KeyDownEvent: public KeyEvent {
		public:
			KeyDownEvent(KeyCode keyCode, uint32 repeatCount): KeyEvent(keyCode), repeatCount(repeatCount) {}

			inline uint32 getRepeatCount() { return repeatCount; }

			EVENT_CLASS_TYPE(KeyDown)

		private:
			uint32 repeatCount;
		};
		class KeyUpEvent: public KeyEvent {
		public:
			KeyUpEvent(KeyCode keyCode): KeyEvent(keyCode) {}

			EVENT_CLASS_TYPE(KeyUp)
		};

		class KeyTypedEvent: public KeyEvent {
		public:
			KeyTypedEvent(const KeyCode keycode)
			    : KeyEvent(keycode) {}

			EVENT_CLASS_TYPE(KeyTyped)
		};
	}
}
