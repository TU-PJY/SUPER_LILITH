#pragma once
#include "ObjectBase.h"
#include "PlayerShape.h"
#include <array>

enum Shape 
{EnumTriangle, EnumSquare, EnumPentagon, EnumHexagon};

class Player : public OBJ_BASE {
private:
	int ShapeState{ EnumTriangle };
	GLfloat Rotation{};

	Triangle triangle;
	Square square;
	Pentagon pentagon;
	Hexagon hexagon;

	GLfloat RotateSpeed = 35;

public:
	Player();
	void Update(float FT);
	void Render();
	void RenderShapes();
	void InputSpecialKey(int KEY, bool KeyDown);
	GLfloat GetRotation();
	int GetShapeState();
	void SetRotateSpeed(GLfloat Speed);
};

