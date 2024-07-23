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
	Tayo::Ref<Tayo::VertexArray> m_SquareVA;
	Tayo::Ref<Tayo::Shader> m_FlatColorShader;

	Tayo::Ref<Tayo::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};