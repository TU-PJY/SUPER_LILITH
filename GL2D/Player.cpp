#include "Player.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
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

	if (PlaySpeed < 1.0 && !GameOver) {
		PlaySpeed = std::lerp(PlaySpeed, 1.0, FT * 3);
		soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);
		RotateSpeed = std::lerp(RotateSpeed, 45, FT * 3);
	}

	Size = std::lerp(Size, 0.5, FT * 25);

	if (GameOver)
		RotateSpeed = std::lerp(RotateSpeed, 0.0, FT * 2.5);

	Rotation += FT * RotateSpeed;

	if (Rotation > 360)
		Rotation = 0;

	switch (ShapeState) {
	case EnumTriangle:
		ShapeRotation = std::lerp(ShapeRotation, 0.0, FT * 15);
		break;
	case EnumSquare:
		ShapeRotation = std::lerp(ShapeRotation, -90, FT * 15);
		break;
	case EnumPentagon:
		ShapeRotation = std::lerp(ShapeRotation, -180, FT * 15);
		break;
	case EnumHexagon:
		ShapeRotation = std::lerp(ShapeRotation, -240, FT * 15);
		break;
	}

	Scale(Size, Size);
	Rotate(Rotation + ShapeRotation + 30);

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