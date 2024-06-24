#include "Obstacle.h"
#include "ImageUtil.h"
#include "FWM.h"

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

	Size -= FT * MoveSpeed;

	Scale(Size, Size);
	Rotate(Rotation + 30);

	if (Size <= 0.4)
		fw.DeleteSelf(this);
}

void Obstacle::Render() {
	ProcessTransform();
	imageUtil.Draw(Image);
}