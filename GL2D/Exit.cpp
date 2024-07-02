#include "Exit.h"
#include "FWM.h"
#include "ExitScreen.h"
#include "Cursor.h"
#include "Button.h"

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
	fw.DeleteObject("cursor", DeleteRange::One);
	fw.DeleteObject("button", DeleteRange::One);
	fw.AddObject(new ExitScreen, "exit_screen", Layer::L3, true);

	return __func__;
}

void Exit::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	// Normal Key Down
	if (KeyDown && !SpecialKey)
		switch (KEY) {
		case 27:
			fw.AddObject(new Button, "button", Layer::L2);
			fw.AddObject(new Cursor, "cursor", Layer::L2);
			fw.EndFloatingMode();
			break;
		}
}

void Exit::MouseButton(int button, int state, int x, int y) {
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