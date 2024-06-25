#include "Obstacle.h"
#include "ImageUtil.h"
#include "FWM.h"
#include <cmath>

Obstacle::Obstacle(ObstacleType type){
	switch (type) {
	case ObstacleType::Triangle:
		Image = imageUtil.SetImage("obstacle_triangle");
		break;

	case ObstacleType::Square:
		Image = imageUtil.SetImage("obstacle_square");
		break;

	case ObstacleType::Pentagon:
		Image = imageUtil.SetImage("obstacle_pentagon");
		break;

	case ObstacleType::Hexagon:
		Image = imageUtil.SetImage("obstacle_hexagon");
		break;
	}

	SetColor(1.0, 1.0, 1.0);
}

void Obstacle::Update(float FT) {
	InitTransform();

	auto player = fw.Find("player", SearchRange::One, Layer::L2);
	if (player) Rotation = player->GetRotation();

	if (Size <= 0.65) {
		Size -= FT * MoveSpeed * 4 * Size;
		if (Size <= 0)
			fw.DeleteSelf(this);
	}

	else {
		Size -= FT * MoveSpeed * Size;
	}

	Scale(Size, Size);
	Rotate(Rotation + 30);
}

void Obstacle::Render() {
	ProcessTransform();
	imageUtil.Draw(Image);
}