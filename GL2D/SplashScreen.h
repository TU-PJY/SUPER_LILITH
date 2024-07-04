#pragma once
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "DataUtil.h"
#include "TextUtil.h"
#include "FWM.h"
#include "Intro.h"

class SplashScreen : public OBJ_BASE {
private:
	unsigned int Image{};
	TextUtil Text;
	GLfloat Delay{};
	int Step = 1;
	bool ImageUtilInitEnd{}, SoundUtilInitEnd{}, DataUtilInitEnd{};
	
public:
	SplashScreen() {
		SetBackgroundColor(0.424, 0.376, 0.412);
		Text.Init(L"Galiver Sans", FW_BOLD, TRUE);
		Text.Draw(ASP(-0.9), 0.65, 0.3, "SUPER LILITH");
		Text.Draw(ASP(-0.9), -0.85, 0.4, "Loading...");

		imageUtil.LoadImageFromFile("splash_image", "resources//image//splash//splash_image.png");
		Image = imageUtil.SetImage("splash_image");
		Scale(imageUtil.Aspect(800, 400) * 2.0, 2.0);
	}

	void Update(float FT) {
		ProcessTransform();
		imageUtil.Draw(Image);
		Text.Draw(ASP(-0.9), 0.65, 0.3, "SUPER LILITH");
		Text.Draw(ASP(-0.9), -0.85, 0.3, "Loading...");

		Delay += FT;

		if (Delay >= 2) {
			if (!ImageUtilInitEnd) {
				imageUtil.LoadImageFromList();
				ImageUtilInitEnd = true;
			}

			if (!SoundUtilInitEnd) {
				soundUtil.Init();
				SoundUtilInitEnd = true;
			}

			if (!DataUtilInitEnd) {
				dataUtil.Init();
				DataUtilInitEnd = true;
			}

			glutFullScreen();
			SetBackgroundColor(0.0, 0.0, 0.0);
			fw.SwitchMode(Intro::IntroMode, Intro::SetController);
		}
	}
};