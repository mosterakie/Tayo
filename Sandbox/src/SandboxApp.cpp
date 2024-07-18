#include <Tayo.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

using namespace Tayo;

class ExampleLayer : public Tayo::Layer
{
public:
	ExampleLayer()
		:Layer("Example layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Tayo::Ref<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Tayo::Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
			)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			uniform vec3 u_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = vec4(u_Color, 1.0);
			}
		)";
		m_Shader.reset(Tayo::Shader::Create(vertexSrc, fragmentSrc));


		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Tayo::Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2 ,2 , 3, 0};

		Tayo::Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Tayo::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Tayo::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Tayo::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Tayo::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Tayo::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Tayo::Timestep ts) override
	{
		
		if (Tayo::Input::IsKeyPressed(TY_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Tayo::Input::IsKeyPressed(TY_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Tayo::Input::IsKeyPressed(TY_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Tayo::Input::IsKeyPressed(TY_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Tayo::Input::IsKeyPressed(TY_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Tayo::Input::IsKeyPressed(TY_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Tayo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tayo::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Tayo::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Tayo::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Tayo::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_Color);

		/*for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Tayo::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		}

		Tayo::Renderer::Submit(m_Shader, m_VertexArray);*/

		m_Texture->Bind();
		Tayo::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		Tayo::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Tayo::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));
		ImGui::End();
	}

	void OnEvent(Tayo::Event& event) override
	{
		
	}
private:
	Tayo::Ref<Tayo::Shader> m_Shader;
	Tayo::Ref<Tayo::Shader> m_SquareShader, m_TextureShader;

	Tayo::Ref<Tayo::VertexArray> m_VertexArray;
	Tayo::Ref<Tayo::VertexArray> m_SquareVA;

	Tayo::Ref<Tayo::Texture2D> m_Texture, m_ChernoLogoTexture;

	Tayo::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Tayo::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}

	 
};

Tayo::Application* Tayo::CreateApplication() {
	return new Sandbox();
}