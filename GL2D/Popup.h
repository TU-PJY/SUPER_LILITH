#pragma once
#include "FWM.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "CameraUtil.h"
#include <cmath>

class PopUp : public OBJ_BASE {
private:
	unsigned int Image{};
	GLfloat Size{0.0};
	GLfloat Num1{}, Num2{}, Num3{};
	GLfloat Delay{};
	GLfloat RotNum{};
	GLfloat Rotation{};

	bool HidePopup{};
	bool SoundPlayed{};

public:
	PopUp() {
		Image = imageUtil.SetImage("popup");
		Translate(-0.75, 0.0);
		ScaleSpot(imageUtil.Aspect(750, 512) * Size, Size);
	}

	void Stop() {
		HidePopup = true;
	}

	void Update(float FT) {
		if (!HidePopup) {
			Delay += FT;
			if (Delay >= 1) {
				if (!SoundPlayed) {
					soundUtil.PlaySound("popup", "ch_ui");
					SoundPlayed = true;
				}

				Size = BounceAnimation(0.5, 5, 0.5, 20, 5, FT);
				RotNum += FT * 10;
				Rotation = sin(RotNum);
			}
		}
		else
			Size = std::lerp(Size, 0.0, FT * 10);
	}

	GLfloat BounceAnimation(GLfloat Size, GLfloat SizeUpSpeed, GLfloat BounceValue,  GLfloat BounceSpeed, GLfloat BounceReduceSpeed, float FrameTime) {
		Num3 += FrameTime * SizeUpSpeed;

		if (Num3 >= Size) {
			Num3 = Size;
			Num1 += FrameTime * BounceSpeed;
			Num2 = std::lerp(Num2, BounceValue, FrameTime * BounceReduceSpeed);
		}

		return Num3 + sin(Num1) * (BounceValue - Num2);
	}

	void Render() {
		InitTransform();
		Translate(-0.75, 0.0);
		RotateSpot(Rotation);
		ScaleSpot(imageUtil.Aspect(750, 512) * Size, Size);
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};