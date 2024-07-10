#pragma once

#include "Tayo/Input.h"

namespace Tayo {
	class WindowsInput :public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int KeyCode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}