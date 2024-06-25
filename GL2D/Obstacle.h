#pragma once
#include "ObjectBase.h"
#include "ImageUtil.h"

enum class ObstacleType 
{Triangle, Square, Pentagon, Hexagon};

class Obstacle : public OBJ_BASE {
private:
	unsigned int Image{};
	int ShapeType{};
	GLfloat Size = 16;
	GLfloat Rotation{};
	GLfloat MoveSpeed = 1.5;

	bool Checked{};
	bool B_ObstacleAdded{};

public:
	Obstacle(ObstacleType type, GLfloat R, GLfloat G, GLfloat B);
	void SetMoveSpeed(GLfloat Speed);
	void Update(float FT);
	bool CheckShapeType();
	void Render();
};

#include <iostream>
class BlinkingObstacle : public OBJ_BASE {
private:
	int ShapeType{};
	unsigned int Image{};
	float Frame{};

	glm::vec3 ColorSet{};

public:
	BlinkingObstacle(int Type, GLfloat R, GLfloat G, GLfloat B, GLfloat Rotation, GLfloat Size) {
		switch (Type) {
		case 0:
			Image = imageUtil.SetImage("obstacle_triangle");
			break;

		case 1:
			Image = imageUtil.SetImage("obstacle_square");
			break;

		case 2:
			Image = imageUtil.SetImage("obstacle_pentagon");
			break;

		case 3:
			Image = imageUtil.SetImage("obstacle_hexagon");
			break;

		}

		SetColor(R, G, B);

		ColorSet.r = R;
		ColorSet.g = G;
		ColorSet.b = B;

		Rotate(Rotation + 30);
		Scale(Size, Size);

	}

	void Update(float FT) {
		Frame += FT * 10;

		if (Frame < 8) {
			if (int(Frame) % 2 == 0)
				SetColor(1.0, 0.0, 0.0);
			else
				SetColor(ColorSet.r, ColorSet.g, ColorSet.b);
		}

		else
			SetColor(1.0, 0.0, 0.0);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};

