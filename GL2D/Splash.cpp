#include "Splash.h"
#include "SplashScreen.h"
#include "FWM.h"

void Splash::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Splash::SplashMode() {
	fw.AddObject(new SplashScreen, "splash_screen", Layer::L1);

	return __func__;
}

void Splash::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {}
void Splash::MouseButton(int button, int state, int x, int y) {}
void Splash::MouseWheel(int button, int Wheel, int x, int y) {}

void Splash::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true);
}

void Splash::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false);
}

void Splash::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Splash::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);
}

void Splash::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Splash::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}