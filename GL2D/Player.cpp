#include "Player.h"
#include "ImageUtil.h"
#include <cmath>

void Player::InputSpecialKey(int KEY, bool KeyDown) {
	if (!GameOver) {
		if (KeyDown) {
			switch (KEY) {
			case GLUT_KEY_RIGHT:
				if (ShapeState < 3)
					ShapeState += 1;
				break;

			case GLUT_KEY_LEFT:
				if (ShapeState > 0)
					ShapeState -= 1;
				break;
			}
		}
	}
}

GLfloat Player::GetRotation(){
	return Rotation;
}

int Player::GetShapeState() {
	return ShapeState;
}

void Player::SetRotateSpeed(GLfloat Speed) {
	RotateSpeed = Speed;
}

void Player::SetSize(GLfloat SizeValue) {
	Size += SizeValue;
}

void Player::SetGameOver() {
	GameOver = true;
}

Player::Player(){
	SetColor(1.0, 1.0, 1.0);
	Scale(Size, Size);

	triangle.Init();
	square.Init();
	pentagon.Init();
	hexagon.Init();
}

void Player::Update(float FT){
	InitTransform();

	Size = std::lerp(Size, 0.5, FT * 25);

	if (GameOver)
		RotateSpeed = std::lerp(RotateSpeed, 0.0, FT * 2.5);

	Rotation += FT * RotateSpeed;

	if (Rotation > 360)
		Rotation = 0;

	Scale(Size, Size);

	Rotate(Rotation + 30);

}

void Player::Render(){
	RenderShapes();
}

void Player::RenderShapes() {
	ProcessTransform();

	if (ShapeState == EnumTriangle)
		triangle.Render();

	else if (ShapeState == EnumSquare)
		square.Render();

	else if (ShapeState == EnumPentagon)
		pentagon.Render();

	else if (ShapeState == EnumHexagon)
		hexagon.Render();

}