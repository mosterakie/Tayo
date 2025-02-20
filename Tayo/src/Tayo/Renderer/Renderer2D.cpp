#include "typch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Tayo {
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		//float TilingFactor;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture
	};


	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		TY_PROFILE_FUNCTION();
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" }
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		// Set all texture slots to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		

	}

	void Renderer2D::Shutdown()
	{
		TY_PROFILE_FUNCTION();

		//delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{

		TY_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		


		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		TY_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		if (dataSize > 0) {
			// 打印数据大小和指针地址
			/*TY_CORE_TRACE("Uploading vertex data: size={} bytes, from={} to={}",
				dataSize,
				(void*)s_Data.QuadVertexBufferBase,
				(void*)s_Data.QuadVertexBufferPtr);*/

			s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
		}

		Flush();

	}

	void Renderer2D::Flush()
	{
		TY_PROFILE_FUNCTION();
		//断点位置

		TY_CORE_ASSERT(s_Data.TextureSlots[0] != nullptr, "White texture not bound!");

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		//TY_PROFILE_FUNCTION();
		TY_CORE_ASSERT(position.z >= -1.0f && position.z <= 1.0f, "Quad Z position out of camera range");

		// 检查 size 是否为正值
		TY_CORE_ASSERT(size.x > 0.0f && size.y > 0.0f, "Quad size must be positive");

		/*TY_CORE_TRACE("Positon X :{}  Y : {}", position.x, position.y);
		TY_CORE_TRACE("size X :{}  Y : {}",size.x,size.y);*/

		const float texIndex = 0.0f; // White Texture

		
		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
		/*TY_CORE_TRACE("Vertex 0: Position=({}, {}, {}), Color=({}, {}, {}, {}), TexCoord=({}, {}), TexIndex={}",
			s_Data.QuadVertexBufferPtr->Position.x, s_Data.QuadVertexBufferPtr->Position.y, position.z,
			s_Data.QuadVertexBufferPtr->Color.r, s_Data.QuadVertexBufferPtr->Color.g, s_Data.QuadVertexBufferPtr->Color.b, s_Data.QuadVertexBufferPtr->Color.a,
			s_Data.QuadVertexBufferPtr->TexCoord.x, s_Data.QuadVertexBufferPtr->TexCoord.y,
			texIndex);*/
		s_Data.QuadVertexBufferPtr++;



		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
		/*TY_CORE_TRACE("Vertex 1: Position=({}, {}, {}), Color=({}, {}, {}, {}), TexCoord=({}, {}), TexIndex={}",
			s_Data.QuadVertexBufferPtr->Position.x, s_Data.QuadVertexBufferPtr->Position.y, position.z,
			s_Data.QuadVertexBufferPtr->Color.r, s_Data.QuadVertexBufferPtr->Color.g, s_Data.QuadVertexBufferPtr->Color.b, s_Data.QuadVertexBufferPtr->Color.a,
			s_Data.QuadVertexBufferPtr->TexCoord.x, s_Data.QuadVertexBufferPtr->TexCoord.y,
			texIndex);*/
		s_Data.QuadVertexBufferPtr++;



		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
		/*TY_CORE_TRACE("Vertex 3: Position=({}, {}, {}), Color=({}, {}, {}, {}), TexCoord=({}, {}), TexIndex={}",
			s_Data.QuadVertexBufferPtr->Position.x, s_Data.QuadVertexBufferPtr->Position.y, position.z,
			s_Data.QuadVertexBufferPtr->Color.r, s_Data.QuadVertexBufferPtr->Color.g, s_Data.QuadVertexBufferPtr->Color.b, s_Data.QuadVertexBufferPtr->Color.a,
			s_Data.QuadVertexBufferPtr->TexCoord.x, s_Data.QuadVertexBufferPtr->TexCoord.y,
			texIndex);*/
		s_Data.QuadVertexBufferPtr++;


		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
		/*TY_CORE_TRACE("Vertex 4: Position=({}, {}, {}), Color=({}, {}, {}, {}), TexCoord=({}, {}), TexIndex={}",
			s_Data.QuadVertexBufferPtr->Position.x, s_Data.QuadVertexBufferPtr->Position.y, position.z,
			s_Data.QuadVertexBufferPtr->Color.r, s_Data.QuadVertexBufferPtr->Color.g, s_Data.QuadVertexBufferPtr->Color.b, s_Data.QuadVertexBufferPtr->Color.a,
			s_Data.QuadVertexBufferPtr->TexCoord.x, s_Data.QuadVertexBufferPtr->TexCoord.y,
			texIndex);*/
		s_Data.QuadVertexBufferPtr++;


		s_Data.QuadIndexCount += 6;

		// 添加调试输出
		//TY_CORE_TRACE("Adding quad at ({}, {}, {}) with texture index {}", position.x, position.y, position.z);


		/*s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		//TY_PROFILE_FUNCTION();

		TY_CORE_ASSERT(position.z >= -1.0f && position.z <= 1.0f, "Quad Z position out of camera range");

		// 检查 size 是否为正值
		TY_CORE_ASSERT(size.x > 0.0f && size.y > 0.0f, "Quad size must be positive");

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;

		for(uint32_t i = 0;i<s_Data.TextureSlotIndex;i++)
		{
			/*if(*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			} */
			if (s_Data.TextureSlots[i] == texture) { // 直接比较 shared_ptr
				textureIndex = (float)i;
				break;
			}
		}


		if(textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x,position.y , 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x,position.y + size.y , 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x ,position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex; 
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		// 添加调试输出
		//TY_CORE_TRACE("Adding quad at ({}, {}, {}) with texture index {}", position.x, position.y, position.z, textureIndex);


#if 0
		s_Data.TextureShader->SetFloat4("u_Color", glm::vec4(1.0f,1.0f,1.0f,1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
#endif

	}

	void Renderer2D::DrawSubTexture(
		const glm::vec3& position,
		const glm::vec2& size,
		const Ref<Texture2D>& atlasTexture,
		const glm::vec2& uvOffset,
		const glm::vec2& uvScale
	) {
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		float textureIndex = 0.0f;

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			/*if(*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			} */
			if (s_Data.TextureSlots[i] == atlasTexture) { // 直接比较 shared_ptr
				textureIndex = (float)i;
				break;
			}
		}


		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = atlasTexture;
			s_Data.TextureSlotIndex++;
		}

		// 顶点1：左下角
		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = uvOffset + glm::vec2(0.0f, 0.0f) * uvScale;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		// 顶点2：右下角
		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = uvOffset + glm::vec2(1.0f, 0.0f) * uvScale;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		// 顶点3：右上角
		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = uvOffset + glm::vec2(1.0f, 1.0f) * uvScale;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		// 顶点4：左上角
		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = uvOffset + glm::vec2(0.0f, 1.0f) * uvScale;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
	}
}