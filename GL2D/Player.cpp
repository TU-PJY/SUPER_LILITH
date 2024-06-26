#include "Player.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "FWM.h"
#include <cmath>

void Player::InputSpecialKey(int KEY, bool KeyDown) {
	if (!GameOver) {
		if (KeyDown) {
			switch (KEY) {
			case GLUT_KEY_RIGHT:
				if (ShapeState < 2)
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

bool Player::GetGameOverState() {
	return GameOver;
}


Player::Player(){
	SetColor(1.0, 1.0, 1.0);
	Scale(Size, Size);

	triangle.Init();
	square.Init();
	pentagon.Init();
}

void Player::Update(float FT){
	InitTransform();

	if (PlaySpeed < 1.0 && !GameOver) {
		PlaySpeed = std::lerp(PlaySpeed, 1.0, FT * 3);
		soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);
	}

	if (!GameOver) {
		auto score = fw.Find("game_score", SearchRange::One, Layer::L3);
		if (score) {
			if (score->GetTime() >= 20 && score->GetTime() < 40)
				RotateSpeed = 20;

			else if (score->GetTime() >= 40 && score->GetTime() < 60)
				RotateSpeed = 35;

			else if (score->GetTime() >= 60 && score->GetTime() > 80)
				RotateSpeed = 50;

			else if (score->GetTime() >= 80 && score->GetTime() < 100)
				RotateSpeed = 65;

			else if(score->GetTime() >= 100)
				RotateSpeed = 100;
		}
	}

	else
		RotateSpeed = std::lerp(RotateSpeed, 0.0, FT * 2.5);

	Rotation += FT * RotateSpeed;
	if (Rotation > 360)
		Rotation = 0;

	Size = std::lerp(Size, 0.5, FT * 25);

	switch (ShapeState) {
	case EnumTriangle:
		ShapeRotation = std::lerp(ShapeRotation, 0.0, FT * 15);
		break;
	case EnumSquare:
		ShapeRotation = std::lerp(ShapeRotation, -120, FT * 15);
		break;
	case EnumPentagon:
		ShapeRotation = std::lerp(ShapeRotation, -192, FT * 15);
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

	switch (ShapeState) {
	case EnumTriangle:
		triangle.Render();
		break;

	case EnumSquare:
		square.Render();
		break;

	case EnumPentagon:
		pentagon.Render();
		break;
	}
}