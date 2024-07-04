#include "DataReset.h"
#include "DataResetScreen.h"
#include "FWM.h"

void DataReset::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string DataReset::DataResetMode() {
	soundUtil.SetFreqCutOff("ch_bgm", 200);
	fw.AddObject(new DataResetScreen, "data_reset_screen", Layer::L3, true);
	return __func__;
}

void DataReset::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	auto data_reset_screen = fw.Find("data_reset_screen");
	if (data_reset_screen) data_reset_screen->InputKey(KEY, KeyDown);
}

void DataReset::MouseButton(int button, int state, int x, int y) {
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

void DataReset::MouseWheel(int button, int Wheel, int x, int y) {
	if (Wheel > 0) {
	}

	else if (Wheel < 0) {
	}
}


void DataReset::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true);
}

void DataReset::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false);
}

void DataReset::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void DataReset::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);
}

void DataReset::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void DataReset::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}