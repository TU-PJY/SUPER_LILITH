#include "Pause.h"
#include "FWM.h"
#include "Lobby.h"
#include "MusicPlayer.h"
#include "SoundUtil.h"

void Pause::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Pause::PauseMode() {
	soundUtil.PauseSound("ch_bgm", true);
	return __func__;
}

void Pause::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	// Normal Key Down
	if (KeyDown && !SpecialKey)
		switch (KEY) {
		case 27:
			soundUtil.PauseSound("ch_bgm", false);
			fw.EndFloatingMode();
			break;

		case 13:
			soundUtil.PauseSound("ch_bgm", false);
			fw.SwitchMode(Lobby::LobbyMode, Lobby::SetController);
			break;
		}
}

void Pause::MouseButton(int button, int state, int x, int y) {
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

void Pause::MouseWheel(int button, int Wheel, int x, int y) {
	if (Wheel > 0) {
	}

	else if (Wheel < 0) {
	}
}


void Pause::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true);
}

void Pause::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false);
}

void Pause::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Pause::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);
}

void Pause::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Pause::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}