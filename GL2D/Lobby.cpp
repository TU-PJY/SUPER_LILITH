#include "Lobby.h"
#include "FWM.h"
#include "Title.h"
#include "Button.h"
#include "MusicPlayer.h"
#include "Stage1.h"
#include "AnimationShape.h"
#include "LobbyPlayer.h"
#include "White.h"
#include "Popup.h"
#include "DataUtil.h"

#include "Exit.h"
#include <string>

void Lobby::SetController() {
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutMouseWheelFunc(MouseWheel);
	glutMouseFunc(MouseButton);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
}

std::string Lobby::LobbyMode() {
	fw.AddObject(new White, "white", Layer::L3);
	fw.AddObject(new Button, "button", Layer::L2);
	fw.AddObject(new Title(mp.MusicNumber), "title", Layer::L2);
	fw.AddObject(new LobbyPlayer, "lobby_player", Layer::L2);

	if (dataUtil.LoadData("Play Once") == 0) {
		fw.AddObject(new PopUp, "popup", Layer::L2);
	}

	if(!mp.MusicPlayerInitState)
		mp.Init("stage_easy");	
	mp.SetToLobbyMode();

	return __func__;
}

void Lobby::ProcessKeyboard(unsigned char KEY, int S_KEY, bool KeyDown, bool SpecialKey) {
	// Normal Key Down
	if (KeyDown && !SpecialKey)
		switch (KEY) {
		case 27:
			{
			auto title = fw.Find("title");
			if(title && !title->GetAnimationtate())
				fw.StartFloatingMode(Exit::ExitMode, Exit::SetController);
			}
			break;
		}

	auto button = fw.Find("button");
	if (button) button->InputKey(KEY, KeyDown);
}

void Lobby::MouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		auto button = fw.Find("button");
		if (button) button->ClickButton();
	}
}

void Lobby::MouseWheel(int button, int Wheel, int x, int y) {
	if (Wheel > 0) {
	}

	else if (Wheel < 0) {
	}
}


void Lobby::KeyDown(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, true, false);

	auto title = fw.Find("title");
	if (title) title->InputKey(KEY, true);
}

void Lobby::KeyUp(unsigned char KEY, int x, int y) {
	ProcessKeyboard(KEY, NULL, false, false);
}

void Lobby::SpecialKeyUp(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, true, true);
}

void Lobby::SpecialKeyDown(int KEY, int x, int y) {
	ProcessKeyboard(NULL, KEY, false, true);

	auto title = fw.Find("title");
	if (title) title->InputSpecialKey(KEY, true);
}

void Lobby::MouseMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}

void Lobby::MousePassiveMotion(int x, int y) {
	mouse.ConvertPosition(x, y);
}