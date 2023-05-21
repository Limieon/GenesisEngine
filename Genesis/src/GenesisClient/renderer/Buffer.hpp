#pragma once
#include "GenesisClient/Defines.hpp"

#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace client {
		enum class ShaderDataType { NONE = 0, FLOAT, FLOAT2, FLOAT3, FLOAT4, MAT3, MAT4, INT, INT2, INT3, INT4, BOOL };
		static uint32 shaderDataTypeSize(ShaderDataType type) {
			switch(type) {
				case ShaderDataType::FLOAT: return 4;
				case ShaderDataType::FLOAT2: return 4 * 2;
				case ShaderDataType::FLOAT3: return 4 * 3;
				case ShaderDataType::FLOAT4: return 4 * 4;
				case ShaderDataType::INT: return 4;
				case ShaderDataType::INT2: return 4 * 2;
				case ShaderDataType::INT3: return 4 * 3;
				case ShaderDataType::INT4: return 4 * 4;
				case ShaderDataType::MAT3: return 4 * 3 * 3;
				case ShaderDataType::MAT4: return 4 * 4 * 4;
				case ShaderDataType::BOOL: return 1;
			}
			GE_Fatal("Unknown shader data type!");
			return 0;
		}

		struct BufferElement {
			String name;
			ShaderDataType type;
			uint32 size;
			uint32 offset;
			bool normalized;

			BufferElement() {}
			BufferElement(ShaderDataType type, const String& name, bool normalized = false)
			    : name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized) {}

			uint32 getComponentCount() const {
				switch(type) {
					case ShaderDataType::FLOAT: return 1;
					case ShaderDataType::FLOAT2: return 2;
					case ShaderDataType::FLOAT3: return 3;
					case ShaderDataType::FLOAT4: return 4;
					case ShaderDataType::INT: return 1;
					case ShaderDataType::INT2: return 2;
					case ShaderDataType::INT3: return 3;
					case ShaderDataType::INT4: return 4;
					case ShaderDataType::MAT3: return 3 * 3;
					case ShaderDataType::MAT4: return 4 * 4;
					case ShaderDataType::BOOL: return 1;
				}
				GE_Fatal("Unknown shader data type!");
				return 0;
			}
		};

		class BufferLayout {
		public:
			BufferLayout() {}

			BufferLayout(const std::initializer_list<BufferElement>& elements): elements(elements) { calculateOffsetAndStride(); }

			inline const std::vector<BufferElement>& getElements() const { return elements; }
			inline const uint32 getStride() const { return stride; }

			std::vector<BufferElement>::iterator begin() { return elements.begin(); }
			std::vector<BufferElement>::iterator end() { return elements.end(); }
			std::vector<BufferElement>::reverse_iterator rbegin() { return elements.rbegin(); }
			std::vector<BufferElement>::reverse_iterator rend() { return elements.rend(); }

		private:
			void calculateOffsetAndStride() {
				uint32 offset = 0;
				stride = 0;

				for(BufferElement& element: elements) {
					element.offset = offset;
					offset += element.size;
					stride += element.size;
				}
			}

			std::vector<BufferElement> elements;
			uint32 stride;
		};

		class IVertexBuffer {
		public:
			virtual ~IVertexBuffer() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;
			virtual void setData(const void* data, size_t size) = 0;

			virtual void setLayout(const BufferLayout& layout) = 0;
			virtual const BufferLayout& getLayout() const = 0;

			static Ref<IVertexBuffer> create(size_t size);
			static Ref<IVertexBuffer> create(const void* data, size_t size);
		};

		class IIndexBuffer {
		public:
			virtual ~IIndexBuffer() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual uint32 getCount() const = 0;

			static Ref<IIndexBuffer> create(uint32* indices, uint32 count);
		};
	}
}
