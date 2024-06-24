#include "Player.h"
#include "ImageUtil.h"
#include "FWM.h"
#include <cmath>

void Player::InputSpecialKey(int KEY, bool KeyDown) {
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

Player::Player(){
	SetColor(1.0, 1.0, 1.0);
	Scale(0.5, 0.5);

	triangle.Init();
	square.Init();
	pentagon.Init();
	hexagon.Init();
}

void Player::Update(float FT){
	InitTransform();

	Scale(0.5, 0.5);

	//Rotation -= FT * 150;
	if (Rotation > 360)
		Rotation = 0;

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