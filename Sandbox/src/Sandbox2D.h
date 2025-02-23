#pragma once

#include "Tayo.h"



//temp
struct TileTexture
{
	Tayo::Ref<Tayo::Texture2D> texture;
	glm::vec2 uvOffset;
	glm::vec2 uvScale;

	TileTexture () = default;

	TileTexture(const std::string& path, float texWidth, float texHeight, float subWidth, float subHeight)
	{
		texture = Tayo::Texture2D::Create(path);
		uvScale = { subWidth / texWidth, subHeight / texHeight };
	};

	Tayo::Ref<Tayo::Texture2D> GetTexture2D()
	{
		return texture;
	}

	glm::vec2 GetUVOffset(float row, float col)
	{
		return { col * uvScale.x, row * uvScale.y };
	}

	glm::vec2 GetUVScale()
	{
		return uvScale;
	}
};



class Sandbox2D : public Tayo::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Tayo::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Tayo::Event& e) override;
private:
	Tayo::OrthographicCameraController m_CameraController;

	// Temp
	TileTexture m_Orc_IdleTextures;
	glm::vec2 Orc_Position = { 0.0f, 0.0f };
	int curr_Orc = 0;
	float speed = 2.0f;


	Tayo::Ref<Tayo::Texture2D> m_TayoTexture;


	TileTexture m_GrassTexture;
	TileTexture m_HillsTexture;
	TileTexture m_WallTexture;
	TileTexture m_WaterTexture;
};