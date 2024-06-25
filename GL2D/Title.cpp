#include "Title.h"
#include "ImageUtil.h"

Title::Title() {
	Image = imageUtil.SetImage("title");
	SetColor(1.0, 1.0, 1.0);

	text.Init(L"열정그자체", FW_NORMAL);
	text.SetAlign(Align::Middle);
}

void Title::Update(float FT) {
	InitTransform();

	Scale(0.8, 0.8);
	Scale(imageUtil.Aspect(1500, 500), 1.0);

	Translate(0.0, 0.7);
}

void Title::Render() {
	ProcessTransform();
	imageUtil.Draw(Image);

	switch (LobbyPage) {
	case 1:
		text.Draw(0.0, 0.4, 0.1, "DJ Striden - Charisma V.I.P");
		break;

	case 2:
		text.Draw(0.0, 0.4, 0.1, "DJ Striden - Celestial Donimion");
		break;

	case 3:
		text.Draw(0.0, 0.4, 0.1, "DJ Striden - Sky Voyager");
		break;

	case 4:
		text.Draw(0.0, 0.4, 0.1, "DJ Striden - Cyber Bunked");
		break;
	}
}

void Title::ChangeLobbyPage(int dir) {
	switch (dir) {
	case 0:
		if (LobbyPage > 1)
			LobbyPage -= 1;
		break;

	case 1:
		if (LobbyPage < 4)
			LobbyPage += 1;
		break;
	}
}
