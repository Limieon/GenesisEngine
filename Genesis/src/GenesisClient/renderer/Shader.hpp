#pragma once
#include "GenesisClient/Defines.hpp"

#include <glm/glm.hpp>

namespace ge {
	namespace client {
		class IShader {
		public:
			virtual const String& getName() const = 0;

			static Ref<IShader> create(const String& file);
			static Ref<IShader> create(const String& name, const String& vertexSrc, const String& fragmentSrc);

		public:
			virtual ~IShader() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			// Functions using vecotrs
			inline bool setUniform2f(const String& uniform, const glm::vec2& vec) const { return setUniform2f(uniform, vec.x, vec.y); }
			inline bool setUniform3f(const String& uniform, const glm::vec3& vec) const { return setUniform3f(uniform, vec.x, vec.y, vec.z); }
			inline bool setUniform4f(const String& uniform, const glm::vec4& vec) const { return setUniform4f(uniform, vec.x, vec.y, vec.z, vec.w); }
			// Functions using matrices
			virtual bool setUniformMatrix4fv(const String& uniform, const glm::mat4& data) const = 0;

			// Raw value Functions
			virtual bool setUniform1f(const String& uniform, float32 x) const = 0;
			virtual bool setUniform2f(const String& uniform, float32 x, float32 y) const = 0;
			virtual bool setUniform3f(const String& uniform, float32 x, float32 y, float32 z) const = 0;
			virtual bool setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a) const = 0;
			virtual bool setUniform1i(const String& uniform, int32 x) const = 0;
			virtual bool setUniform2i(const String& uniform, int32 x, int32 y) const = 0;
			virtual bool setUniform3i(const String& uniform, int32 x, int32 y, int32 z) const = 0;
			virtual bool setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a) const = 0;
			virtual bool setUniform1b(const String& uniform, bool x) const = 0;

			// Array Functions
			virtual bool setUniformIArray(const String& uniform, int32* values, uint32 count) const = 0;
		};

		class ShaderLibrary {
		public:
			void add(const Ref<IShader>& shader);
			void add(const String& name, const Ref<IShader>& shader);
			Ref<IShader> load(const String& file);
			Ref<IShader> load(const String& name, const String& file);

			Ref<IShader> get(const String& name);

			inline const bool exists(const String& name) const { return shaders.find(name) != shaders.end(); }

		private:
			std::unordered_map<String, Ref<IShader>> shaders;
		};
	}
}
