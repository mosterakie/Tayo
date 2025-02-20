#pragma once

#include <string>

#include "Tayo/Core/Core.h"

namespace Tayo {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(const std::string& path,uint32_t OroginX, uint32_t OroginY, uint32_t width, uint32_t height);


		virtual Ref<Texture2D> GetSubTexture(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) const = 0;
	};

}