#include "Stage1.h"
#include "FWM.h"
#include "Player.h"
#include "ObstacleGenerator.h"
#include "MusicPlayer.h"
#include "GameScore.h"
#include "CameraUtil.h"

void Stage_1::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Stage_1::Stage1() {
	fw.AddObject(new Player, "player", Layer::L2);
	fw.AddObject(new ObstacleGenerator, "obstacle_generator", Layer::L2);
	fw.AddObject(new GameScore, "game_score", Layer::L3);
	mp.SetToPlayMode();

	return __func__;
}

void Stage_1::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	// Normal Key Down
	if (KeyDown && !SpecialKey)
		switch (KEY) {
		case 27:
			glutDestroyWindow(1);
			break;
		}
}

void Stage_1::MouseButton(int button, int state, int x, int y) {
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

void Stage_1::MouseWheel(int button, int Wheel, int x, int y) {
	if (Wheel > 0) {
	}

	else if (Wheel < 0) {
	}
}


void Stage_1::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true, false);
}

void Stage_1::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false, false);
}

void Stage_1::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Stage_1::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);

	auto player = fw.Find("player");
	if (player) player->InputSpecialKey(KEY, true);
}

void Stage_1::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Stage_1::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}