#include "Shader.hpp"

#include "GenesisClient/platform/opengl/OpenGLShader.hpp"
#include "RendererAPI.hpp"

namespace ge {
	namespace client {
		Ref<IShader> IShader::create(const String& name, const String& vertexSrc, const String& fragmentSrc) {
			switch(GE_getRendererAPI()) {
				case GE_RENDERER_API_None: GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RENDERER_API_OpenGL: return createRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			}
			return nullptr;
		}
		Ref<IShader> IShader::create(const String& file) {
			switch(GE_getRendererAPI()) {
				case GE_RENDERER_API_None: GE_Assert(false, "RendererAPI::None is currently not supported!"); return nullptr;
				case GE_RENDERER_API_OpenGL: return createRef<OpenGLShader>(file);
			}
			return nullptr;
		}

		void ShaderLibrary::add(const String& name, const Ref<IShader>& shader) {
			GE_Assert(!exists(name), "Shader already exists!");
			shaders[name] = shader;
		}
		void ShaderLibrary::add(const Ref<IShader>& shader) {
			auto& name = shader->getName();
			add(name, shader);
		}

		Ref<IShader> ShaderLibrary::load(const String& file) {
			auto shader = IShader::create(file);
			add(shader);
			return shader;
		}
		Ref<IShader> ShaderLibrary::load(const String& name, const String& file) {
			auto shader = IShader::create(file);
			add(name, shader);
			return shader;
		}
		Ref<IShader> ShaderLibrary::get(const String& name) {
			GE_Assert(exists(name), "Shader not found!");
			return shaders[name];
		}
	}
}
