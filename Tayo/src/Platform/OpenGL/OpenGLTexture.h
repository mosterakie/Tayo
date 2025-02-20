#pragma once

#include "Tayo/Renderer/Texture.h"
#include <glad/glad.h>

namespace Tayo {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(const std::string& path, uint32_t originX, uint32_t originY, uint32_t width, uint32_t height);

		//Not Done Yet
		virtual Ref<Texture2D> GetSubTexture(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) const override
		{
			Ref<OpenGLTexture2D> subTexture = CreateSubTexture(originX, originY, width, height);
			return subTexture;
		}
		//
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;


		//Not Done Yet
		Ref<OpenGLTexture2D> OpenGLTexture2D::CreateSubTexture(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) const;
		//
	};
}