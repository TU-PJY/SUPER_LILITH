#include "Exit.h"
#include "FWM.h"
#include "ExitScreen.h"
#include "Button.h"
#include "SoundUtil.h"

void Exit::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Exit::ExitMode() {
	soundUtil.PlaySound("exit_sound", "ch_ui");
	soundUtil.SetFreqCutOff("ch_bgm", 200);
	fw.AddObject(new ExitScreen, "exit_screen", Layer::L3, true);

	return __func__;
}

void Exit::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	auto exitscreen = fw.Find("exit_screen");
	if (exitscreen) {
		if(!SpecialKey)
			exitscreen->InputKey(KEY, KeyDown);
	}
}

void Exit::MouseButton(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		switch (state) {
		case GLUT_DOWN:
		{
			auto exitscreen = fw.Find("exit_screen");
			if (exitscreen) exitscreen->ClickButton();
		}
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

void Exit::MouseWheel(int button, int Wheel, int x, int y) {}

void Exit::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true);
}

void Exit::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false);
}

void Exit::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Exit::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);
}

void Exit::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Exit::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}