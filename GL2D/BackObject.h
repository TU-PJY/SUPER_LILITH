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
	GLfloat Size = 0.5;

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

	void SetSize(GLfloat SizeValue) {
		Size += SizeValue;
	}

	void Update(float FT) {
		auto title = fw.Find("title");
		if (title)  ObjectColor = title->GetColorSet();

		InitTransform();

		if (Transparent)
			AlphaValue = std::lerp(AlphaValue, 0.0, FT * 10);

		Height -= FT * 0.5;
		if (Height < -1.5)
			fw.DeleteSelf(this);

		Rotation += FT * 20;

		Size = std::lerp(Size, 0.5, FT * 15);

		Translate(Position, Height);
		RotateSpot(Rotation);
		ScaleSpot(Size, Size);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}

	void SetTransparent() {
		Transparent = true;
	}
};