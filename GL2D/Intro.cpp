#include "Intro.h"
#include "FWM.h"
#include "Logo.h"

void Intro::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Intro::IntroMode() {
	fw.AddObject(new Logo, "logo", Layer::L1);
		
	return __func__;
}

void Intro::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {}
void Intro::MouseButton(int button, int state, int x, int y) {}
void Intro::MouseWheel(int button, int Wheel, int x, int y) {}

void Intro::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true);
}

void Intro::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false);
}

void Intro::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Intro::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);
}

void Intro::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Intro::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}