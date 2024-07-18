#include "typch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tayo {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}