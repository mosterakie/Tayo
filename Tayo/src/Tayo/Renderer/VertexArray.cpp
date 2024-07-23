#include "typch.h"

#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Tayo {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    TY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}
		TY_CORE_ASSERT(false, "Unknown RendererAPI!");
	}
}