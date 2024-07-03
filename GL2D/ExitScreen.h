#pragma once
#include "FWM.h"
#include "Button.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "CameraUtil.h"
#include "TextUtil.h"
#include "SoundUtil.h"
#include <cmath>

class ExitScreen : public OBJ_BASE {
private:
	unsigned int BackImage{};
	TextUtil Text;
	GLfloat TextAlpha{};
	GLfloat TextSize{};

public:
	ExitScreen() {
		Text.Init(L"열정그자체", FW_NORMAL, TRUE);
		Text.SetAlign(Align::Middle);

		BackImage = imageUtil.SetImage("black_front");

		Scale(ASP(10.0), 10.0);

		AlphaValue = 0.0;
		TextAlpha = 0.0;
		TextSize = 0.3;
	}

	void InputKey(unsigned char KEY, bool KeyDown) {
		if (KeyDown) {
			switch (KEY) {
			case 13:
				glutDestroyWindow(1);
				break;

			case 27:
				soundUtil.UnSetFreqCutOff("ch_bgm");
				fw.EndFloatingMode();
				break;

			}
		}
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
		Text.Draw(0.0, DivideZoom(0.5, cam.Zoom), DivideZoom(0.5 + TextSize, cam.Zoom), "EXIT?");
		Text.Draw(0.0, 0.0, DivideZoom(0.3 + TextSize, cam.Zoom), "Press Enter To Exit");
	}
};