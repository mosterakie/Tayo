#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f)
{
	m_CameraController.SetCameraZoomLevel(2.0f);
}

void Sandbox2D::OnAttach()
{
	TY_PROFILE_FUNCTION();
	m_TayoTexture = Tayo::Texture2D::Create("assets/textures/Tilesets/Grass.png");

	m_Orc_IdleTextures = TileTexture("assets/textures/Orc-Idle.png", 600.0f, 100.0f, 100.0f, 100.0f);
	m_GrassTexture = TileTexture("assets/textures/Tilesets/Grass.png", 176.0f,112.0f,16.0f,16.0f);
	m_HillsTexture = TileTexture("assets/textures/Tilesets/Hills.png", 176.0f, 112.0f, 16.0f, 16.0f);
	m_WallTexture = TileTexture("assets/textures/Tilesets/Wooden_House_Walls_Tilset.png", 80.0f, 48.0f, 16.0f, 16.0f);
	m_WaterTexture = TileTexture("assets/textures/Tilesets/Water.png", 64.0f, 16.0f, 16.0f, 16.0f);
}

void Sandbox2D::OnDetach()
{
	TY_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Tayo::Timestep ts)
{

	TY_PROFILE_FUNCTION();
	// Update
	
	m_CameraController.OnUpdate(ts);

	curr_Orc += ts.GetMilliseconds();
	

	// Render
	{
		TY_PROFILE_SCOPE("Renderer Prep");
		Tayo::RenderCommand::SetClearColor({ 0.0f, 1.0f, 1.0f, 1 });
		Tayo::RenderCommand::Clear();
	}

	{
		TY_PROFILE_SCOPE("Renderer Draw");

		Tayo::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (float i = -3.8; i < 3.8; i += 0.16)
		{
			for (float j = -2; j < 2; j+=0.16)
			{
				Tayo::Renderer2D::DrawSubTexture({ i, j, -0.2f }, { 0.16f, 0.16f }, m_GrassTexture.GetTexture2D(), m_GrassTexture.GetUVOffset(0, 0), m_GrassTexture.GetUVScale());
			}
		}

		for(float i = -3.8; i < -1; i += 0.16)
		{
			for (float j = 2; j > 1.5; j -= 0.16)
			{
				Tayo::Renderer2D::DrawSubTexture({ i, j, -0.1f }, { 0.16f, 0.16f }, m_HillsTexture.GetTexture2D(), m_HillsTexture.GetUVOffset(5,1), m_HillsTexture.GetUVScale());
			}
		}

		for (float i = -3.8; i <-1; i += 0.16)
		{
			Tayo::Renderer2D::DrawSubTexture({ i, 1.36, -0.1f }, { 0.16f, 0.16f }, m_HillsTexture.GetTexture2D(), m_HillsTexture.GetUVOffset(4,1), m_HillsTexture.GetUVScale());
		}

		Tayo::Renderer2D::DrawSubTexture({ -0.92, 1.36, -0.1f }, { 0.16f, 0.16f }, m_HillsTexture.GetTexture2D(), m_HillsTexture.GetUVOffset(4, 2), m_HillsTexture.GetUVScale());

		for (float i = 1.36; i < 2; i += 0.16)
		{
			Tayo::Renderer2D::DrawSubTexture({ -0.92, i, -0.1f }, { 0.16f, 0.16f }, m_HillsTexture.GetTexture2D(), m_HillsTexture.GetUVOffset(5, 2), m_HillsTexture.GetUVScale());
		}


		for (float i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Tayo::Renderer2D::DrawSubTexture({ i*0.16, j*0.16, 0.0f }, { 0.16f, 0.16f }, m_WallTexture.GetTexture2D(), m_WallTexture.GetUVOffset(j,i), m_WallTexture.GetUVScale());
			}
		}


		for (float i = 0.16 * 10; i >-1; i -= 0.16)
		{
			for (float j = -0.16 * 10; j > -3; j -= 0.16)
			{
				Tayo::Renderer2D::DrawSubTexture({ i, j, 0.0f }, { 0.16f, 0.16f }, m_WaterTexture.GetTexture2D(), m_WaterTexture.GetUVOffset(int(i/0.16)%4,0), m_WaterTexture.GetUVScale());
			}
		}

		curr_Orc += ts * 100;
		curr_Orc %= 6;
		Tayo::Renderer2D::DrawSubTexture({ Orc_Position.x, Orc_Position .y, 0.5f}, { 1.0f, 1.0f }, m_Orc_IdleTextures.GetTexture2D(), m_Orc_IdleTextures.GetUVOffset(0,curr_Orc), m_Orc_IdleTextures.GetUVScale());


		Tayo::Renderer2D::EndScene();
	}

	{
		TY_PROFILE_SCOPE("Input");

		if (Tayo::Input::IsKeyPressed(TY_KEY_UP)) {
			TY_CORE_INFO("UP key is pressed!");
			Orc_Position.y += speed * ts;
		}
		else if (Tayo::Input::IsKeyPressed(TY_KEY_DOWN)) {
			TY_CORE_INFO("DOWN key is pressed!");
			Orc_Position.y -= speed * ts;
		}
		else if (Tayo::Input::IsKeyPressed(TY_KEY_LEFT)) {
			TY_CORE_INFO("LEFT key is pressed!");
			Orc_Position.x -= speed * ts;
		}
		else if (Tayo::Input::IsKeyPressed(TY_KEY_RIGHT)) {
			TY_CORE_INFO("RIGHT key is pressed!");
			Orc_Position.x += speed * ts;

		}else if(Tayo::Input::IsKeyPressed(TY_KEY_ESCAPE)){
			quick_exit(0);
		}
	}
	

}

void Sandbox2D::OnImGuiRender()
{
	TY_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::BulletText("Test Text");
	ImGui::End();
}

void Sandbox2D::OnEvent(Tayo::Event& e)
{
	m_CameraController.OnEvent(e);
}