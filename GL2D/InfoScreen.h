#pragma once
#include "ImageUtil.h"
#include "TextUtil.h"
#include "ObjectBase.h"
#include "CameraUtil.h"
#include <cmath>

class InfoScreen : public OBJ_BASE {
private:
	unsigned int Back{};
	unsigned int FMOD_Logo{};
	TextUtil Text;
	GLfloat BackAlpha{};
	GLfloat Scroll{};

public:
	InfoScreen() {
		Back = imageUtil.SetImage("black_front");
		FMOD_Logo = imageUtil.SetImage("FMOD_logo");

		Text.Init(L"Galiver Sans", FW_BOLD, TRUE);

		Text.SetAlign(Align::Middle);
		Scale(ASP(10.0), 10.0);
		Scroll = -2.0;
	}

	void Update(float FT) {
		BackAlpha = std::lerp(BackAlpha, 0.7, FT * 10);
		Scroll += FT * 0.2;

		if (Scroll >= 3.4)
			Scroll = -2.0;
	}

	void Render() {
		InitTransform();
		SetColor(0.0, 0.0, 0.0);
		AlphaValue = BackAlpha;
		Scale(ASP(10.0), 10.0);
		ProcessTransform();
		imageUtil.Draw(Back);
		

		Text.Draw(0.0, DivideZoom(0.6 + Scroll, cam.Zoom), 
			DivideZoom(0.45, cam.Zoom), "SUPER LILITH");

		Text.Draw(0.0, DivideZoom(0.3 + Scroll, cam.Zoom),
			DivideZoom(0.15, cam.Zoom), "A Computer Game By MATA_");

		Text.Draw(0.0, DivideZoom(0.0 + Scroll, cam.Zoom),
			DivideZoom(0.15, cam.Zoom), "Powered By MATA_ENGINE-1");

		Text.Draw(0.0, DivideZoom(-0.3 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "- Music -");
		Text.Draw(0.0, DivideZoom(-0.45 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "[DJ-Striden] - Crystallize");
		Text.Draw(0.0, DivideZoom(-0.6 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "[DJ-Striden] - Level Two");
		Text.Draw(0.0, DivideZoom(-0.75 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "[DJ-Striden] - Hyper Octane");
		Text.Draw(0.0, DivideZoom(-0.9 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "[DJ-Striden] - Candy Stealing Zombies");
		Text.Draw(0.0, DivideZoom(-1.05 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "[DJ-Striden] - Sentient");

		Text.Draw(0.0, DivideZoom(-1.2 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "(P) 2015-2022 DJ-Striden");

		Text.Draw(0.0, DivideZoom(-1.45 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "Made using FMOD Studio by Firelight Technologies Pty Ltd.");

		InitTransform();
		SetColor(1.0, 1.0, 1.0);
		Translate(0.0, DivideZoom(-1.8 + Scroll, cam.Zoom));
		ScaleSpot(DivideZoom(imageUtil.Aspect(2000, 679) * 0.5, cam.Zoom), DivideZoom(0.5, cam.Zoom));
		AlphaValue = 1.0;
		ProcessTransform();
		imageUtil.Draw(FMOD_Logo);

		Text.Draw(0.0, DivideZoom(-2.3 + Scroll, cam.Zoom),
			DivideZoom(0.1, cam.Zoom), "Copyleft 2024 MATA_");
	}
};

