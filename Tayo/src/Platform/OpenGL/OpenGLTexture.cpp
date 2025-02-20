#include "typch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Tayo {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		TY_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		TY_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		TY_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;


		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		TY_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, uint32_t originX, uint32_t originY, uint32_t width, uint32_t height)
	{
		TY_PROFILE_FUNCTION();

		// 加载整个图像
		int imgWidth, imgHeight, channels;
		stbi_set_flip_vertically_on_load(1); // 确保原点在左上角
		stbi_uc* fullData = stbi_load(path.c_str(), &imgWidth, &imgHeight, &channels, 4);
		TY_CORE_ASSERT(fullData, "Failed to load image!");

		// 检查子区域是否合法
		TY_CORE_ASSERT(originX + width <= (uint32_t)imgWidth, "Subimage exceeds image width!");
		TY_CORE_ASSERT(originY + height <= (uint32_t)imgHeight, "Subimage exceeds image height!");

		//// 确定格式
		GLenum internalFormat = GL_RGBA8,
		dataFormat = GL_RGBA;
		//if (channels == 4) {
		//	internalFormat = GL_RGBA8;
		//	dataFormat = GL_RGBA;
		//}
		//else if (channels == 3) {
		//	internalFormat = GL_RGB8;
		//	dataFormat = GL_RGB;
		//}

		

		TY_CORE_ASSERT(internalFormat && dataFormat, "Unsupported image format!");
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		// 提取子区域像素数据
		std::vector<stbi_uc> subData(width * height * channels);
		for (uint32_t y = 0; y < height; ++y) {
			const stbi_uc* src = fullData + ((originY + y) * imgWidth + originX) * channels;
			stbi_uc* dst = subData.data() + y * width * channels;
			std::memcpy(dst, src, width * channels * sizeof(stbi_uc));
		}

		// 创建OpenGL纹理
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);

		// 设置纹理参数
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 像素风建议使用NEAREST
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// 上传子图像数据
		glTextureSubImage2D(
			m_RendererID, 0,
			0, 0, // 目标偏移
			width, height,
			GL_RGBA, GL_UNSIGNED_BYTE,
			subData.data()
		);

		// 清理资源
		stbi_image_free(fullData);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		TY_PROFILE_FUNCTION();

		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		TY_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		TY_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		TY_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}


	Ref<OpenGLTexture2D> OpenGLTexture2D ::CreateSubTexture(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) const
	{
		// 创建一个新的纹理对象，作为子纹理
		Ref<OpenGLTexture2D> subTexture = std::make_shared<OpenGLTexture2D>(width, height);

		// 将原纹理的部分数据拷贝到子纹理
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, originX, originY, width, height, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);

		// 设置子纹理的参数
		glBindTexture(GL_TEXTURE_2D, 0);

		return subTexture;
	}
}