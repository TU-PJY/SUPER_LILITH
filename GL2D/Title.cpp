#include "Title.h"
#include "ImageUtil.h"
#include <cmath>

Title::Title() {
	Image = imageUtil.SetImage("title");
	SetColor(1.0, 1.0, 1.0);

	text.Init(L"열정그자체", FW_NORMAL);
	text.SetAlign(Align::Middle);
}

void Title::InputSpecialKey(int KEY, bool KeyDown) {
	if (KeyDown) {
		switch (KEY) {
		case GLUT_KEY_LEFT:
			if (LobbyPage > 1) {
				LobbyPage -= 1;
				TitlePosition = 0.3;
			}
			break;

		case GLUT_KEY_RIGHT:
			if (LobbyPage < 4) {
				LobbyPage += 1;
				TitlePosition = -0.3;
			}
			break;
		}
	}
}

void Title::Update(float FT) {
	InitTransform();

	Scale(0.8, 0.8);
	Scale(imageUtil.Aspect(1500, 500), 1.0);

	Translate(0.0, 0.7);

	TitlePosition = std::lerp(TitlePosition, 0.0, FT * 10);
}

void Title::Render() {
	ProcessTransform();
	imageUtil.Draw(Image);

	switch (LobbyPage) {
	case 1:
		text.Draw(TitlePosition, 0.4, 0.1, "DJ Striden - Charisma V.I.P");
		break;

	case 2:
		text.Draw(TitlePosition, 0.4, 0.1, "DJ Striden - Celestial Donimion");
		break;

	case 3:
		text.Draw(TitlePosition, 0.4, 0.1, "DJ Striden - Sky Voyager");
		break;

	case 4:
		text.Draw(TitlePosition, 0.4, 0.1, "DJ Striden - Cyber Bunked");
		break;
	}
}

void Title::ChangeLobbyPage(int dir) {
	switch (dir) {
	case 0:  // left
		if (LobbyPage > 1) {
			LobbyPage -= 1;
			TitlePosition = 0.3;
		}
		break;

	case 1:  // right
		if (LobbyPage < 4) {
			LobbyPage += 1;
			TitlePosition = -0.3;
		}
		break;
	}
}
