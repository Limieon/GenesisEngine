#include "OpenGLShader.hpp"

#include <GenesisCore/Logger.hpp>
#include <glad/glad.h>

namespace ge {
	namespace client {
		namespace Utils {
			static GLenum shaderTypeFromString(const String& str) {
				if(str == "vertex") return GL_VERTEX_SHADER;
				if(str == "fragment") return GL_FRAGMENT_SHADER;

				GE_Fatal("Unknown shader type");
				return 0;
			}
		}

		OpenGLShader::OpenGLShader(const String& file) {
			String src = readFile(file);
			auto shaders = preProcess(src);
			compile(shaders);

			// Extract name from filepath
			auto lastSlash = file.find_last_of("/\\");
			lastSlash = lastSlash == String::npos ? 0 : lastSlash + 1;
			auto lastDot = file.rfind(".");
			auto count = lastDot == String::npos ? file.size() - lastSlash : lastDot - lastSlash;

			name = file.substr(lastSlash, count);
		}
		OpenGLShader::OpenGLShader(const String& name, const String& vertexSrc, const String& fragmentSrc): name(name) {
			std::unordered_map<GLenum, std::string> shaders;
			shaders[GL_VERTEX_SHADER] = vertexSrc;
			shaders[GL_FRAGMENT_SHADER] = fragmentSrc;
			compile(shaders);
		}

		OpenGLShader::~OpenGLShader() { glDeleteProgram(handle); }

		String OpenGLShader::readFile(const String& file) {
			GE_Info("Compiling {0}...", file);

			std::ifstream in(file, std::ios::in | std::ios::binary);
			String res;
			if(in) {
				in.seekg(0, std::ios::end);
				res.resize(in.tellg());

				in.seekg(0, std::ios::beg);
				in.read(&res[0], res.size());
			} else {
				GE_Error("Could not read from file '{0}'", file);
			}
			return res;
		}
		std::unordered_map<GLenum, String> OpenGLShader::preProcess(const String& src) {
			std::unordered_map<GLenum, String> shaders;
			const char* typeToken = "#type";
			size_t typeToken_legnth = strlen(typeToken);

			size_t pos = src.find(typeToken, 0);
			while(pos != String::npos) {
				size_t eol = src.find_first_of("\r\n", pos);
				GE_Assert(eol != String::npos, "Syntax Error");
				size_t begin = pos + typeToken_legnth + 1;
				String type = src.substr(begin, eol - begin);
				GE_Assert(Utils::shaderTypeFromString(type), "Invalid Shader Type specified");

				size_t nextLinePos = src.find_first_not_of("\r\n", eol);
				GE_Assert(nextLinePos != String::npos, "Syntax Error");
				pos = src.find(typeToken, nextLinePos);

				shaders[Utils::shaderTypeFromString(type)] =
				    src.substr(nextLinePos, pos - (nextLinePos == String::npos ? src.size() - 1 : nextLinePos));
			}

			return shaders;
		}
		void OpenGLShader::compile(const std::unordered_map<GLenum, String>& shaders) {
			GE_Assert(shaders.size() <= 5, "Only a maxmimum of 5 shaders is supported");
			GLuint program = glCreateProgram();
			std::array<GLenum, 5> shaderIDs;
			int32 index = 0;
			for(auto& kv: shaders) {
				GLenum type = kv.first;
				const String& src = kv.second;

				GLuint shader = glCreateShader(type);
				const GLchar* source = src.c_str();

				glShaderSource(shader, 1, &source, 0);
				glCompileShader(shader);

				GLint isCompiled = 0;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
				if(isCompiled == GL_FALSE) {
					GLint maxLength = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

					std::vector<GLchar> infoLog(maxLength);
					glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

					glDeleteShader(shader);

					GE_Error("{0}", infoLog.data());
					GE_Assert(false, "Shader compilation failure!");
					break;
				}
				glAttachShader(program, shader);
				shaderIDs[index++] = shader;
			}
			handle = program;

			glLinkProgram(handle);

			GLint isLinked;
			glGetProgramiv(handle, GL_LINK_STATUS, (int*) &isLinked);
			if(isLinked == GL_FALSE) {
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
				glDeleteProgram(program);

				GE_Error("{0}", infoLog.data());
				GE_Assert(false, "Shader link failure!");

				for(auto id: shaderIDs) {
					glDeleteShader(id);
				}
			}

			for(uint8 i = 0; i < index; ++i) {
				glDetachShader(handle, shaderIDs[i]);
			}
		}

		void OpenGLShader::bind() const { glUseProgram(handle); }
		void OpenGLShader::unbind() const { glUseProgram(0); }

		bool OpenGLShader::setUniform1f(const String& uniform, float32 x) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform1f(location, x);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform1f(location, x);
			return true;
#endif
		}
		bool OpenGLShader::setUniform2f(const String& uniform, float32 x, float32 y) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform2f(location, x, y);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform2f(location, x, y);
			return true;
#endif
		}
		bool OpenGLShader::setUniform3f(const String& uniform, float32 x, float32 y, float32 z) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform3f(location, x, y, z);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform3f(location, x, y, z);
			return true;
#endif
		}
		bool OpenGLShader::setUniform4f(const String& uniform, float32 x, float32 y, float32 z, float32 a) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform4f(location, x, y, z, a);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform4f(location, x, y, z, a);
			return true;
#endif
		}
		bool OpenGLShader::setUniform1i(const String& uniform, int32 x) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform1i(location, x);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform1i(location, x);
			return true;
#endif
		}
		bool OpenGLShader::setUniform2i(const String& uniform, int32 x, int32 y) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform2i(location, x, y);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform2i(location, x, y);
			return true;
#endif
		}
		bool OpenGLShader::setUniform3i(const String& uniform, int32 x, int32 y, int32 z) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform3i(location, x, y, z);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform3i(location, x, y, z);
			return true;
#endif
		}
		bool OpenGLShader::setUniform4i(const String& uniform, int32 x, int32 y, int32 z, int32 a) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform4i(location, x, y, z, a);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform4i(location, x, y, z, a);
			return true;
#endif
		}
		bool OpenGLShader::setUniform1b(const String& uniform, bool x) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				if(x) {
					glUniform1i(location, 1);
				} else {
					glUniform1i(location, 0);
				}

				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			if(x) {
				glUniform1i(location, 1);
			} else {
				glUniform1i(location, 0);
			}
			return true;
#endif
		}

		bool OpenGLShader::setUniformMatrix4fv(const String& uniform, const glm::mat4& data) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]);
			return true;
#endif
		}

		bool OpenGLShader::setUniformIArray(const String& uniform, int32* values, uint32 count) const {
			int32 location = glGetUniformLocation(handle, uniform.c_str());

#ifdef GE_DEBUG
			if(location != -1) {
				glUniform1iv(location, count, values);
				return true;
			} else {
				GE_Warn("Uniform '{0}' not found!", uniform);
				return false;
			}
#else
			glUniform1iv(location, count, values);
			return true;
#endif
		}
	}
}
