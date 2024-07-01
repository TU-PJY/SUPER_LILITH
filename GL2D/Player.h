#pragma once
#include "ObjectBase.h"
#include "PlayerShape.h"
#include <array>
#include <random>

enum Shape 
{EnumTriangle, EnumSquare, EnumPentagon, EnumHexagon};

class Player : public OBJ_BASE {
private:
	int ShapeState{ EnumTriangle };
	GLfloat Rotation{};
	GLfloat ShapeRotation{};
	GLfloat Size = 0.6;

	Triangle triangle;
	Square square;
	Pentagon pentagon;
	Hexagon hexagon;

	GLfloat RotateSpeed{};
	GLfloat PlaySpeed = 0.0;
	GLfloat Direction = 1;

	bool GameOver{};

	unsigned int PlayerImageNormal1{};
	unsigned int PlayerImageNormal2{};
	unsigned int PlayerImageNormal3{};
	unsigned int PlayerImageGameOver{};

	bool BlinkState{};
	bool WinkState{};
	GLfloat BlinkTimer{};
	GLfloat NextTime{20};
	GLfloat BlinkCount{};
	std::random_device rd;

public:
	Player();
	void Update(float FT);
	void Render();
	void RenderShapes();
	void InputSpecialKey(int KEY, bool KeyDown);
	GLfloat GetRotation();
	int GetShapeState();
	void SetRotateSpeed(GLfloat Speed);
	void SetSize(GLfloat Size);
	void SetGameOver();
	bool GetGameOverState();
	void ChangeRotationDirection();
	void UpdateBlink(float FT);
};