#pragma once
#include "FWM.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include <random>
#include <cmath>

class BackObject : public OBJ_BASE {
private:
	unsigned int Image{};
	GLfloat Rotation{};
	GLfloat Position{}, Height{};
	int Type{};
	std::random_device rd;
	bool Transparent{};

public:
	BackObject() {
		std::uniform_int_distribution uid{ 1, 3 };
		std::uniform_real_distribution urd{-1.0, 1.0};
		Type = uid(rd);
		Position = ASP(urd(rd));
		Height = 1.5;

		switch (Type) {
		case 1:
			Image = imageUtil.SetImage("center_triangle");
			break;
		case 2:
			Image = imageUtil.SetImage("center_square");
			break;
		case 3:
			Image = imageUtil.SetImage("center_pentagon");
			break;
		}

		AlphaValue = 0.5;
		SetColor(1.0, 1.0, 1.0);
	}

	void Update(float FT) {
		InitTransform();

		if (Transparent)
			AlphaValue = std::lerp(AlphaValue, 0.0, FT * 10);

		Height -= FT * 0.5;
		if (Height < -1.5)
			fw.DeleteSelf(this);

		Rotation += FT * 20;

		Translate(Position, Height);
		RotateSpot(Rotation);
		ScaleSpot(0.5, 0.5);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}

	void SetTransparent() {
		Transparent = true;
	}
};