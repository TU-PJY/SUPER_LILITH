#include "Stage1.h"
#include "FWM.h"
#include "Player.h"

void Mode1::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Mode1::GameMode1() {
	fw.AddObject(new Player, "player", Layer::L2);
	return __func__;
}