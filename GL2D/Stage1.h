#pragma once
#include "MouseUtil.h"
#include "FWM.h"
#include <string>

namespace Mode1 {
	void SetController();
	std::string GameMode1();
}

inline void ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey=false) {
	// Normal Key Down
	if (KeyDown && !SpecialKey) 
		switch (KEY) {
		case 27:
			glutDestroyWindow(1);
			break;
		}
}

inline void MouseButton(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		switch (state) {
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch (state) {
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;
	}
}

inline void MouseWheel(int button, int Wheel, int x, int y) {
	if (Wheel > 0) {
	}

	else if (Wheel < 0) {
	}
}


inline void KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true);
}

inline void KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false);
}

inline void SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

inline void SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);

	auto player = fw.Find("player", SearchRange::One, Layer::L2);
	if (player) player->InputSpecialKey(KEY, true);
}

inline void MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

inline void MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}