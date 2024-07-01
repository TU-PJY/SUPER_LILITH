#include "Player.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "FWM.h"
#include <cmath>

void Player::InputSpecialKey(int KEY, bool KeyDown) {
	if (!GameOver) {
		if (KeyDown) {
			switch (KEY) {
			case GLUT_KEY_RIGHT: case GLUT_KEY_SHIFT_R:
				if (ShapeState < 2)
					ShapeState += 1;
				break;

			case GLUT_KEY_LEFT: case GLUT_KEY_SHIFT_L:
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

void Player::ChangeRotationDirection() {
	Direction *= -1;
}


Player::Player(){
	switch (Face) {
	case lilith:
		PlayerImageNormal1 = imageUtil.SetImage("lilith_1");
		PlayerImageNormal2 = imageUtil.SetImage("lilith_2");
		PlayerImageNormal3 = imageUtil.SetImage("lilith_3");
		PlayerImageGameOver = imageUtil.SetImage("lilith_4");
		break;
	}

	SetColor(1.0, 1.0, 1.0);
	Scale(Size, Size);

	triangle.Init();
	square.Init();
	pentagon.Init();
}

void Player::UpdateBlink(float FT) {
	BlinkTimer += FT * 10;

	if (BlinkTimer >= NextTime && !BlinkState && !WinkState) {
		++BlinkCount;
		if (BlinkCount >= 10)
			WinkState = true;

		BlinkState = true;
		BlinkTimer = 0;
	}

	if (BlinkTimer >= 2 && BlinkState && !WinkState) {
		std::uniform_int_distribution uid{ 10, 30 };
		NextTime = uid(rd);

		BlinkState = false;
		BlinkTimer = 0;
	}

	if (BlinkState && WinkState && BlinkTimer >= 40) {
		std::uniform_int_distribution uid{ 10, 30 };
		NextTime = uid(rd);

		BlinkState = false;
		WinkState = false;
		BlinkCount = 0;

		BlinkTimer = 0;
	}
}

void Player::Update(float FT){
	InitTransform();

	if (PlaySpeed < 1.0 && !GameOver) {
		PlaySpeed = std::lerp(PlaySpeed, 1.0, FT * 3);
		soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);
	}

	if (!GameOver) {
		auto score = fw.Find("game_score");
		if (score) {
			int Diff = score->GetDiff();

			if (20 <= Diff && Diff < 40)
				RotateSpeed = 20 * Direction;

			else if (40 <= Diff && Diff < 60)
				RotateSpeed = 35 * Direction;

			else if (60 <= Diff && Diff < 80)
				RotateSpeed = 45 * Direction;

			else if (80 <= Diff && Diff < 100)
				RotateSpeed = 55 * Direction;

			else if (100 <= Diff && Diff < 140)
				RotateSpeed = 65 * Direction;

			else if (140 <= Diff)
				RotateSpeed = 80 * Direction;
		}
	}

	else
		RotateSpeed = std::lerp(RotateSpeed, 0.0, FT * 2.5);

	Rotation += FT * RotateSpeed;
	if (Rotation > 360)
		Rotation = 0;

	Size = std::lerp(Size, 0.6, FT * 25);

	switch (ShapeState) {
	case EnumTriangle:
		ShapeRotation = std::lerp(ShapeRotation, 0.0, FT * 25);
		break;
	case EnumSquare:
		ShapeRotation = std::lerp(ShapeRotation, -90, FT * 25);
		break;
	case EnumPentagon:
		ShapeRotation = std::lerp(ShapeRotation, -192, FT * 25);
		break;
	}

	UpdateBlink(FT);

	Scale(Size, Size);
	Rotate(Rotation + ShapeRotation);
}

void Player::Render(){
	RenderShapes();
}

void Player::RenderShapes() {
	SetColor(1.0, 1.0, 1.0);
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

	SetColor(0.0, 0.0, 0.0);
	ProcessTransform();
	if (!GameOver) {
		if(!BlinkState)
			imageUtil.Draw(PlayerImageNormal1);
		else if(BlinkState && WinkState)
			imageUtil.Draw(PlayerImageNormal3);
		else
			imageUtil.Draw(PlayerImageNormal2);
	}
	else
		imageUtil.Draw(PlayerImageGameOver);
}