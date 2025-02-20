#pragma once

#include "Tayo.h"

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
	Tayo::Ref<Tayo::Texture2D> m_CheckerboardTexture;
	Tayo::Ref<Tayo::Shader> m_TextureShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec2 QuadPosition = { 0.0f, 0.0f };
	Tayo::Ref<Tayo::Texture2D> m_TayoTexture;
	std::vector<Tayo::Ref<Tayo::Texture2D>> m_StaticObjectTextures;
	std::vector<Tayo::Ref<Tayo::Texture2D>> m_Orc_IdleTextures;
	int curr_Orc = 0;

	std::vector< Tayo::Ref<Tayo::Texture2D>> m_GrassTextures;

	std::vector<std::vector<int>> m_Map;
};