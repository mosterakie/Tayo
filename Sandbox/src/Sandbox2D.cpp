#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
	
}

void Sandbox2D::OnAttach()
{
	TY_PROFILE_FUNCTION();
	m_CheckerboardTexture = Tayo::Texture2D::Create("assets/textures/CheckerBoard.png");
	m_StaticObjectTextures.push_back(Tayo::Texture2D::Create("assets/textures/objects.png", 5, 0, 56, 111));
	m_TayoTexture = Tayo::Texture2D::Create("assets/textures/Tilesets/Grass.png");

	/*for (int i = 0; i < 6; i++)
	{
		m_Orc_IdleTextures.push_back(Tayo::Texture2D::Create("assets/textures/Orc-Idle.png", 43+100*i, 43, 30, 30));
	}

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_GrassTextures.push_back(Tayo::Texture2D::Create("assets/textures/Tilesets/Grass.png", 16 * i, 16 * j, 16, 16));
		}
	}*/
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
		//Tayo::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f },m_CheckerboardTexture); 
		/*for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 20; j++) {
				Tayo::Renderer2D::DrawQuad({ -1+ i*0.16, -1 + j * 0.16, 0.0f }, { 0.16f, 0.16f }, m_GrassTextures[0]);
			}
		}*/
		float texWidth = 176.0f;   // 大纹理宽度
		float texHeight = 112.0f;  // 大纹理高度
		float subWidth = 16.0f;     // 子纹理宽度
		float subHeight = 16.0f;    // 子纹理高度

		int row = 2;  // 第 3 行（从 0 开始）
		int col = 1;  // 第 2 列

		glm::vec2 uvOffset(col * subWidth / texWidth, row * subHeight / texHeight);
		glm::vec2 uvScale(subWidth / texWidth, subHeight / texHeight);
		Tayo::Renderer2D::DrawSubTexture({ 0.0f, 0.0f, -0.1f }, { 0.16f, 0.16f }, m_TayoTexture, uvOffset, uvScale);
			
		
		Tayo::Renderer2D::DrawQuad({ -1, -1, 0.0f }, { 0.56f, 1.11f }, m_StaticObjectTextures[0]);
		
		//Tayo::Renderer2D::DrawQuad(QuadPosition, { 0.3f, 0.3f}, m_Orc_IdleTextures[curr_Orc%6]);
		//Tayo::Renderer2D::DrawQuad({ 20, 20, 0 }, { 10, 10 }, { 1, 0, 0, 1 }); 
		Tayo::Renderer2D::EndScene();
	}

	{
		TY_PROFILE_SCOPE("Input");
		if (Tayo::Input::IsKeyPressed(TY_KEY_UP)) {
			TY_CORE_INFO("UP key is pressed!");
			QuadPosition.y += 0.01f;
		}
		else if (Tayo::Input::IsKeyPressed(TY_KEY_DOWN)) {
			TY_CORE_INFO("DOWN key is pressed!");
			QuadPosition.y -= 0.01f;
		}
		else if (Tayo::Input::IsKeyPressed(TY_KEY_LEFT)) {
			TY_CORE_INFO("LEFT key is pressed!");
			QuadPosition.x -= 0.01f;
		}
		else if (Tayo::Input::IsKeyPressed(TY_KEY_RIGHT)) {
			TY_CORE_INFO("RIGHT key is pressed!");
			QuadPosition.x += 0.01f;

		}else if(Tayo::Input::IsKeyPressed(TY_KEY_ESCAPE)){
			quick_exit(0);
		}
	}
	

}

void Sandbox2D::OnImGuiRender()
{
	TY_PROFILE_FUNCTION();
	//ImGui::Begin("Settings");
	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	//ImGui::End();
}

void Sandbox2D::OnEvent(Tayo::Event& e)
{
	m_CameraController.OnEvent(e);
}