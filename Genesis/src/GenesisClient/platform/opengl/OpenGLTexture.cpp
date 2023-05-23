#include "OpenGLTexture.hpp"

#include <GenesisCore/Logger.hpp>
#include <glad/glad.h>
#include <stb_image.h>

namespace ge {
	namespace client {
		OpenGLTexture2D::OpenGLTexture2D(const String& path): path(path) {
			int32 w, h, channels;
			stbi_set_flip_vertically_on_load(1);
			stbi_uc* data = stbi_load(path.c_str(), &w, &h, &channels, 0);
			GE_Assert(data, "Failed to load image!");

			width = w;
			height = h;

			internalFormat = 0;
			dataFormat = 0;

			switch(channels) {
				case 4:
					internalFormat = GL_RGBA8;
					dataFormat = GL_RGBA;
					break;
				case 3:
					internalFormat = GL_RGB8;
					dataFormat = GL_RGB;
					break;
			}
			GE_Assert(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &handle);
			glTextureStorage2D(handle, 1, internalFormat, width, height);

			glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(handle, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		OpenGLTexture2D::OpenGLTexture2D(uint32 width, uint32 height): width(width), height(height) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;

			glCreateTextures(GL_TEXTURE_2D, 1, &handle);
			glTextureStorage2D(handle, 1, internalFormat, width, height);
			glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		void OpenGLTexture2D::setData(void* data, uint32 size) {
			GE_Assert(size == width * height * (dataFormat == GL_RGBA ? 4 : 3), "Data must be entire texture!");
			glTextureSubImage2D(handle, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
		}

		OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &handle); }

		void OpenGLTexture2D::bind(uint32 slot) const { glBindTextureUnit(slot, handle); }
	}
}
