#pragma once
#include "ImageUtil.h"
#include "ObjectBase.h"
#include "Lobby.h"
#include "MusicPlayer.h"
#include "SoundUtil.h"
#include <cmath>

class FMOD_Logo : public OBJ_BASE {
private:
	unsigned int Image{};
	GLfloat Size{};
	GLfloat Delay{};

public:
	FMOD_Logo() {
		Image = imageUtil.SetImage("FMOD_logo");
		Size = 1.0;
		AlphaValue = 0.0;

		Scale(Size * imageUtil.Aspect(2000, 679), Size);
		SetColor(1.0, 1.0, 1.0);
	}

	void Update(float FT) {
		InitTransform();
		Delay += FT;

		if (Delay >= 1) {
			if (Size <= 0.52) {
				if (Delay >= 3) {
					AlphaValue -= FT * 2;
					if (AlphaValue <= 0) {
						AlphaValue = 0;
						if (Delay >= 4)
							fw.SwitchMode(Lobby::LobbyMode, Lobby::SetController);
					}
				}
			}

			else {
				Size = std::lerp(Size, 0.5, FT * 10);
				AlphaValue = std::lerp(AlphaValue, 1.0, FT * 10);
			}
		}

		Scale(Size * imageUtil.Aspect(2000, 679), Size);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};


class Logo : public OBJ_BASE {
private:
	unsigned int Image{};
	GLfloat Size{};
	GLfloat Delay{};
	bool SoundPlayed{};

public:
	Logo() {
		Image = imageUtil.SetImage("logo");
		Size = 3.0;
		AlphaValue = 0.0;
		Scale(Size, Size);
	}

	void Update(float FT) {
		InitTransform();
		Delay += FT;

		if (Delay >= 1) {
			if (!SoundPlayed) {
				soundUtil.PlaySound("logo_sound", "ch_ui");
				SoundPlayed = true;
			}

			if (Size <= 1.52) {
				if (Delay >= 3) {
					AlphaValue -= FT * 2;

					if (AlphaValue <= 0) {
						AlphaValue = 0;
						fw.AddObject(new FMOD_Logo, "fmod_logo", Layer::L1);
						fw.DeleteSelf(this);
					}
				}
			}

			else {
				Size = std::lerp(Size, 1.5, FT * 10);
				AlphaValue = std::lerp(AlphaValue, 1.0, FT * 10);
			}
		}

		Scale(Size, Size);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};