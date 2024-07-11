#pragma once

#include "Tayo/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Tayo {
	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		// Í¨¹ý GraphicsContext ¼Ì³Ð
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
	private:
		GLFWwindow* m_WindowHandle;
	};
}