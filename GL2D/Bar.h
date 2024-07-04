#pragma once
#include "FWM.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "TextUtil.h"
#include "CameraUtil.h"
#include <cmath>

class Bar : public OBJ_BASE {
private:
	unsigned int BackImage{};
	unsigned int MusicResetIcon{};
	unsigned int MusicResumeIcon{};
	unsigned int EffectOnIcon{};
	unsigned int EffectOffIcon{};
	TextUtil Text;
	int AlertType;

	GLfloat Delay{};
	GLfloat Height{};

public:
	Bar(int Type) {
		AlertType = Type;
		switch (AlertType) {
		case 1:
			MusicResetIcon = imageUtil.SetImage("icon_music_reset");
			break;
		case 2:
			MusicResumeIcon = imageUtil.SetImage("icon_music_resume");
			break;
		case 3:
			EffectOffIcon = imageUtil.SetImage("icon_effect_off");
			break;
		case 4:
			EffectOnIcon = imageUtil.SetImage("icon_effect_on");
			break;
		}

		BackImage = imageUtil.SetImage("bar");

		Height = -1.2;
		Translate(0.0, Height);

		Text.Init(L"Galiver Sans", FW_BOLD, TRUE);
	}

	void Update(float FT) {
		Delay += FT * 10;

		if(Delay <= 10)
		Height = std::lerp(Height, -0.8, FT * 10);

		else {
			Height = std::lerp(Height, -1.2, FT * 15);
			if (Height >= 11.8)
				fw.DeleteSelf(this);
		}
	}

	void Render() {
		if (fw.Mode() == "LobbyMode") {
			InitTransform();
			AlphaValue = 0.6;
			Translate(0.0, DivideZoom(Height, cam.Zoom));
			ScaleSpot(DivideZoom(0.3 * imageUtil.Aspect(2048, 512), cam.Zoom), DivideZoom(0.3, cam.Zoom));
			ProcessTransform();
			imageUtil.Draw(BackImage);


			InitTransform();
			AlphaValue = 1.0;
			Translate(DivideZoom(-0.4, cam.Zoom), DivideZoom(Height, cam.Zoom));
			ScaleSpot(DivideZoom(0.3, cam.Zoom), DivideZoom(0.3, cam.Zoom));
			ProcessTransform();

			switch (AlertType) {
			case 1:
				imageUtil.Draw(MusicResetIcon);
				Text.Draw(DivideZoom(-0.25, cam.Zoom), DivideZoom(Height - 0.03, cam.Zoom),
					DivideZoom(0.1, cam.Zoom), "Music Replay At Start");
				break;

			case 2:
				imageUtil.Draw(MusicResumeIcon);
				Text.Draw(DivideZoom(-0.28, cam.Zoom), DivideZoom(Height - 0.03, cam.Zoom),
					DivideZoom(0.1, cam.Zoom), "Music Resume At Start");
				break;

			case 3:
				imageUtil.Draw(EffectOffIcon);
				Text.Draw(DivideZoom(-0.1, cam.Zoom), DivideZoom(Height - 0.03, cam.Zoom),
					DivideZoom(0.1, cam.Zoom), "Beat Effect Off");
				break;

			case 4:
				imageUtil.Draw(EffectOnIcon);
				Text.Draw(DivideZoom(-0.1, cam.Zoom), DivideZoom(Height - 0.03, cam.Zoom),
					DivideZoom(0.1, cam.Zoom), "Beat Effect On");
				break;
			}
		}
	}
};
