#include "Info.h"
#include "FWM.h"
#include "InfoScreen.h"
#include "SoundUtil.h"
#include "BlackFront.h"

void Info::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Info::InfoMode() {
	soundUtil.SetFreqCutOff("ch_bgm", 200);
	fw.AddObject(new InfoScreen, "info_screen", Layer::L3, true);
	return __func__;
}

void Info::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	// Normal Key Down
	if (KeyDown && !SpecialKey)
		switch (KEY) {
		case 27:
			soundUtil.PlaySound("click", "ch_ui");
			soundUtil.UnSetFreqCutOff("ch_bgm");
			fw.AddObject(new BlackFront, "black_front", Layer::L3);
			fw.EndFloatingMode();
			break;
		}
}

void Info::MouseButton(int button, int state, int x, int y) {
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

void Info::MouseWheel(int button, int Wheel, int x, int y) {
	if (Wheel > 0) {
	}

	else if (Wheel < 0) {
	}
}


void Info::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true);
}

void Info::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false);
}

void Info::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Info::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);
}

void Info::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Info::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}