#pragma once
#include "GenesisClient/Defines.hpp"
#include "GenesisClient/renderer/Shader.hpp"

// TODO: Remove
typedef unsigned int GLenum;

namespace ge {
	namespace client {
		class OpenGLShader: public IShader {
		public:
			OpenGLShader(const String& file);
			OpenGLShader(const String& name, const String& vertexSrc, const String& fragmentSrc);
			~OpenGLShader();

			virtual void bind() const override;
			virtual void unbind() const override;

			const String& getName() const override { return name; }

			virtual bool setUniform1f(const String& uniform, float32 x) const override;
			virtual bool setUniform2f(const String& uniform, float32 x, float32 y) const override;
			virtual bool setUniform3f(const String& uniform, float32 x, float32 y, float32 z) const override;
			virtual bool setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a) const override;
			virtual bool setUniform1i(const String& uniform, int32 x) const override;
			virtual bool setUniform2i(const String& uniform, int32 x, int32 y) const override;
			virtual bool setUniform3i(const String& uniform, int32 x, int32 y, int32 z) const override;
			virtual bool setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a) const override;
			virtual bool setUniform1b(const String& uniform, bool x) const override;
			virtual bool setUniformMatrix4fv(const String& uniform, const glm::mat4& data) const override;

			virtual bool setUniformIArray(const String& uniform, int32* values, uint32 count) const override;

		private:
			String readFile(const String& file);
			std::unordered_map<GLenum, String> preProcess(const String& src);
			void compile(const std::unordered_map<GLenum, String>& shaders);

			String name;

			uint32 handle;
		};
	}
}
