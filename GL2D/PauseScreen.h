#pragma once
#include "FWM.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "CameraUtil.h"
#include "TextUtil.h"
#include "SoundUtil.h"
#include <cmath>

class PauseScreen : public OBJ_BASE {
private:
	unsigned int BackImage{};
	TextUtil Text;
	GLfloat TextAlpha{};
	GLfloat TextSize{};

public:
	PauseScreen() {
		Text.Init(L"Galiver Sans", FW_BOLD, TRUE);
		Text.SetAlign(Align::Middle);

		BackImage = imageUtil.SetImage("black_front");

		Scale(ASP(10.0), 10.0);

		AlphaValue = 0.0;
		TextAlpha = 0.0;
		TextSize = 0.3;

		auto player = fw.Find("player");
		if (player) player->Stop();
		soundUtil.SetPlaySpeed("ch_bgm", 0.0);
	}

	void Update(float FT) {
		InitTransform();
		Scale(ASP(10.0), 10.0);
		TextAlpha = std::lerp(TextAlpha, 1.0, FT * 10);
		TextSize = std::lerp(TextSize, 0.0, FT * 10);
		AlphaValue = std::lerp(AlphaValue, 0.5, FT * 10);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(BackImage);

		Text.SetAlpha(TextAlpha);
		Text.Draw(0.0, DivideZoom(0.5, cam.Zoom), DivideZoom(0.5 + TextSize, cam.Zoom), "PAUSED");
		Text.Draw(0.0, 0.0, DivideZoom(0.2 + TextSize, cam.Zoom), "Press Enter To Back To Home");
	}
};