#include "Stage1.h"
#include "FWM.h"
#include "Player.h"
#include "ObstacleGenerator.h"
#include "MusicPlayer.h"
#include "GameScore.h"
#include "CameraUtil.h"
#include "Pause.h"

void Play::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Play::PlayMode() {
	fw.AddObject(new Player, "player", Layer::L2);
	fw.AddObject(new ObstacleGenerator, "obstacle_generator", Layer::L2);
	fw.AddObject(new GameScore, "game_score", Layer::L3);
	mp.SetToPlayMode();

	return __func__;
}

void Play::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	// Normal Key Down
	if (KeyDown && !SpecialKey)
		switch (KEY) {
		case 27:
			fw.StartFloatingMode(Pause::PauseMode, Pause::SetController, true);
			break;
		}
}

void Play::MouseButton(int button, int state, int x, int y) {
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

void Play::MouseWheel(int button, int Wheel, int x, int y) {
	if (Wheel > 0) {
	}

	else if (Wheel < 0) {
	}
}


void Play::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true, false);
}

void Play::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false, false);
}

void Play::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Play::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);

	auto player = fw.Find("player");
	if (player) player->InputSpecialKey(KEY, true);
}

void Play::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Play::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}