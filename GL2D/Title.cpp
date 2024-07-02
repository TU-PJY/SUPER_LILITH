#include "Title.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "FWM.h"
#include "MusicPlayer.h"
#include "stage1.h"
#include "AnimationShape.h"
#include "BackObject.h"
#include <cmath>

Title::Title(int Page) {
	SetColor(1.0, 1.0, 1.0);

	Text.Init(L"열정그자체", FW_NORMAL, TRUE);
	Text.SetAlign(Align::Middle);
	Text.SetColor(ObjectColorSet[Page - 1].r, ObjectColorSet[Page - 1].g, ObjectColorSet[Page - 1].b);

	BgmNum = soundUtil.GetSoundNumif("stage");
	SetBackgroundColor(ColorSet[Page - 1].r, ColorSet[Page - 1].g, ColorSet[Page - 1].b);

	LobbyPage = Page;
	UpdateButtonState();
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

				for (int i = 0; i < fw.Size(Layer::L1); ++i) {
					auto back_object = fw.Find("back_object", Layer::L1, i);
					if (back_object) back_object->SetTransparent();
				}

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

	UpdateBackObject(FT);

	if (StartAnimation) {
		TitleMovePosition = std::lerp(TitleMovePosition, 0.8, FT * 3);
		PlaySpeed = std::lerp(PlaySpeed, 0.3, FT * 3);
		soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);

		if(TitleMovePosition >= 0.78)
			fw.SwitchMode(Play::PlayMode, Play::SetController);
	}

	else {
		TitleMovePosition = std::lerp(TitleMovePosition, 0.0, FT * 5);
		PlaySpeed = std::lerp(PlaySpeed, 1.0, FT * 5);
		soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);
	}

	TitlePosition = std::lerp(TitlePosition, 0.0, FT * 10);
}

void Title::Render() {
	Text.Draw(0.0, 0.6 + TitleMovePosition, 0.45, "SUPER LILITH");
	Text.Draw(TitlePosition, 0.3 + TitleMovePosition , 0.3, "%s", MusicInfo[LobbyPage - 1].c_str());
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

	UpdateButtonState();

	SetBackgroundColor(ColorSet[LobbyPage - 1].r, ColorSet[LobbyPage - 1].g, ColorSet[LobbyPage - 1].b);
	Text.SetColor(ObjectColorSet[LobbyPage - 1].r, ObjectColorSet[LobbyPage - 1].g, ObjectColorSet[LobbyPage - 1].b);
}

void Title::UpdateButtonState() {
	if (LobbyPage == BgmNum) {
		auto button = fw.Find("button");
		if (button) button->SetInvisibleRightArrow();
	}

	else if (LobbyPage == 1) {
		auto button = fw.Find("button");
		if (button) button->SetInvisibleLeftArrow();
	}

	else {
		auto button = fw.Find("button");
		if (button) button->SetVisibleArrow();
	}
}

int Title::GetLobbyPage() {
	return LobbyPage;
}

void Title::UpdateBackObject(float FT) {
	if (!StartAnimation) {
		BackObjectTimer += FT * 5;

		if (BackObjectTimer >= 5) {
			fw.AddObject(new BackObject, "back_object", Layer::L1);
			BackObjectTimer = 0;
		}
	}
}

glm::vec3 Title::GetColorSet() {
	return ObjectColorSet[LobbyPage-1];
}
