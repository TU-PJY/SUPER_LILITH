#pragma once
#include "FWM.h"
#include "Button.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "CameraUtil.h"
#include "TextUtil.h"
#include "SoundUtil.h"
#include "BlackFront.h"
#include "DataUtil.h"
#include <cmath>

class DataResetScreen : public OBJ_BASE {
private:
	unsigned int BackImage{};
	GLfloat BackImageAlpha{};
	GLfloat FrontImageAlpha{};

	TextUtil Text;
	GLfloat TextAlpha{};
	GLfloat TextSize{};

	bool AnimationStart{ };

public:
	DataResetScreen() {
		Text.Init(L"Galiver Sans", FW_BOLD, TRUE);
		Text.SetAlign(Align::Middle);

		BackImage = imageUtil.SetImage("black_front");

		Scale(ASP(10.0), 10.0);

		TextAlpha = 0.0;
		TextSize = 0.3;
	}

	void InputKey(unsigned char KEY, bool KeyDown) {
		if (!AnimationStart) {
			if (KeyDown) {
				switch (KEY) {
				case 13:
					AnimationStart = true;
					break;

				case 27:
					soundUtil.PlaySound("click", "ch_ui");
					soundUtil.UnSetFreqCutOff("ch_bgm");
					fw.AddObject(new BlackFront, "black_front", Layer::L3);
					fw.EndFloatingMode();
					break;
				}
			}
		}
	}

	void Update(float FT) {
		TextAlpha = std::lerp(TextAlpha, 1.0, FT * 10);
		TextSize = std::lerp(TextSize, 0.0, FT * 10);
		BackImageAlpha = std::lerp(BackImageAlpha, 0.5, FT * 10);

		if (AnimationStart) {
			FrontImageAlpha += FT * 0.5;
			if (FrontImageAlpha >= 1.0) {
				dataUtil.ResetData();
				glutDestroyWindow(1);
			}
		}
	}

	void Render() {
		InitTransform();
		Scale(ASP(10.0), 10.0);
		SetAlpha(BackImageAlpha);
		ProcessTransform();
		imageUtil.Draw(BackImage);

		Text.SetAlpha(TextAlpha);
		Text.Draw(0.0, DivideZoom(0.5, cam.Zoom), DivideZoom(0.5 + TextSize, cam.Zoom), "Reset Data?");
		Text.Draw(0.0, 0.0, DivideZoom(0.3 + TextSize, cam.Zoom), "Press Enter To Reset");

		Text.Draw(0.0, DivideZoom(-0.3, cam.Zoom), DivideZoom(0.1 + TextSize, cam.Zoom), "All progress will be reset and you will need to restart the game.");
	
		InitTransform();
		Scale(ASP(10.0), 10.0);
		SetAlpha(FrontImageAlpha);
		ProcessTransform();
		imageUtil.Draw(BackImage);
	}
};