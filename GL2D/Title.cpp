#include "Title.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "FWM.h"
#include "MusicPlayer.h"
#include "stage1.h"
#include "AnimationShape.h"
#include <cmath>

Title::Title(int Page) {
	SetColor(1.0, 1.0, 1.0);

	Text.Init(L"열정그자체", FW_NORMAL, TRUE);
	Text.SetAlign(Align::Middle);

	BgmNum = soundUtil.GetSoundNumif("stage");

	LobbyPage = Page;
}

void Title::InputSpecialKey(int KEY, bool KeyDown) {
	if (!StartAnimation) {
		if (KeyDown) {
			switch (KEY) {
			case GLUT_KEY_LEFT:
				ChangeLobbyPage(0);
				break;

			case GLUT_KEY_RIGHT:
				ChangeLobbyPage(1);
				break;
			}
		}
	}
}

void Title::InputKey(unsigned char KEY, bool KeyDown) {
	if (!StartAnimation) {
		if (KeyDown) {
			if (KEY == 32) {
				fw.DeleteObject("lobby_player", DeleteRange::One);
				fw.AddObject(new AnimationShape(1.0, 1.0, 1.0), "ani_shape", Layer::L2);
				auto button = fw.Find("button");
				if (button) button->EnableStartAnimation();
				StartAnimation = true;
			}
		}
	}
}

bool Title::GetAnimationtate() {
	return StartAnimation;
}

void Title::EnableStartAnimation() {
	StartAnimation = true;
}

void Title::Update(float FT) {
	InitTransform();

	if (StartAnimation) {
		TitleMovePosition = std::lerp(TitleMovePosition, 0.8, FT * 3);
		PlaySpeed = std::lerp(PlaySpeed, 0.3, FT * 3);
		soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);

		if(TitleMovePosition >= 0.78)
			fw.SwitchMode(Stage_1::Stage1, Stage_1::SetController);
	}
	else {
		TitleMovePosition = std::lerp(TitleMovePosition, 0.0, FT * 5);
		PlaySpeed = std::lerp(PlaySpeed, 1.0, FT * 5);
		soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);
	}

	TitlePosition = std::lerp(TitlePosition, 0.0, FT * 10);
}

void Title::Render() {
	Text.Draw(0.0, 0.6 + TitleMovePosition, 0.45, "BEAT SHIFTER");
	Text.Draw(TitlePosition, 0.4 + TitleMovePosition , 0.1, "%s", MusicInfo[LobbyPage - 1].c_str());
}

void Title::ChangeLobbyPage(int dir) {
	switch (dir) {
	case 0:  // left
		if (LobbyPage > 1) {
			LobbyPage -= 1;
			TitlePosition = 0.3;

			soundUtil.PlaySound("click", "ch_ui");
			mp.PlayMusic(LobbyPage);
		}
		break;

	case 1:  // right
		if (LobbyPage < BgmNum) {
			LobbyPage += 1;
			TitlePosition = -0.3;

			soundUtil.PlaySound("click", "ch_ui");
			mp.PlayMusic(LobbyPage);
		}
		break;
	}
}

int Title::GetLobbyPage() {
	return LobbyPage;
}
