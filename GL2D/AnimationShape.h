#pragma once
#include "ObjectBase.h"
#include "ImageUtil.h"
#include <cmath>

class AnimationShape : public OBJ_BASE {
private:
	GLfloat Rotation{};
	GLfloat Size = 1.2;
	unsigned int Image{};
	unsigned int PlayerImage{};
	GLfloat Position = -0.2;
	
public:
	AnimationShape(GLfloat R, GLfloat G, GLfloat B) {
		switch (Face) {
		case lilith:
			PlayerImage = imageUtil.SetImage("lilith_3");
			break;
		}

		Image = imageUtil.SetImage("center_triangle");
		Rotation = -180;
		Translate(0.0, Position);
		ScaleSpot(Size, Size);
		RotateSpot(Rotation);
		SetColor(R, G, B);
	}

	void Update(float FT) {
		InitTransform();
		Rotation = std::lerp(Rotation, 0.0, FT * 3.5);
		Size = std::lerp(Size, 0.6, FT * 3.5);
		Position = std::lerp(Position, 0.0, FT * 3.5);

		Translate(0.0, Position);
		ScaleSpot(Size, Size);
		RotateSpot(Rotation);
	}

	void Render() {
		SetColor(1.0, 1.0, 1.0);
		ProcessTransform();
		imageUtil.Draw(Image);

		SetColor(0.0, 0.0, 0.0);
		ProcessTransform();
		imageUtil.Draw(PlayerImage);
	}
};