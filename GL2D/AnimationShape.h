#pragma once
#include "ObjectBase.h"
#include "ImageUtil.h"
#include <cmath>

class AnimationShape : public OBJ_BASE {
private:
	GLfloat Rotation{};
	GLfloat Size = 1.2;
	unsigned int Image{};
	GLfloat Position = -0.2;
	
public:
	AnimationShape(GLfloat R, GLfloat G, GLfloat B) {
		Image = imageUtil.SetImage("center_triangle");
		Rotation = -90;
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
		RotateSpot(Rotation + 30);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};