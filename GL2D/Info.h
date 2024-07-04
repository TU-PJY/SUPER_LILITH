#pragma once
#include "MouseUtil.h"
#include <string>

namespace Info {
	void SetController();
	std::string InfoMode();

	void ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey = false);
	void MouseButton(int button, int state, int x, int y);
	void MouseWheel(int button, int Wheel, int x, int y);
	void KeyDown(unsigned char KEY, int x, int y);
	void KeyUp(unsigned char KEY, int x, int y);
	void SpecialKeyUp(int KEY, int x, int y);
	void SpecialKeyDown(int KEY, int x, int y);
	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
}
