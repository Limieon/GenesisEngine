#pragma once
#include "GenesisClient/Defines.hpp"

namespace ge {
	namespace client {
		class ITexture {
		public:
			virtual ~ITexture() {}

			virtual uint32 getWidth() const = 0;
			virtual uint32 getHeight() const = 0;
			virtual void bind(uint32 slot = 0) const = 0;

			virtual void setData(void* data, uint32 size) = 0;

			virtual bool operator==(const ITexture& other) const = 0;
			virtual bool operator!=(const ITexture& other) const = 0;
		};

		class ITexture2D: public ITexture {
		public:
			static Ref<ITexture2D> create(const String& path);
			static Ref<ITexture2D> create(uint32 width, uint32 height);
		};
	}
}
