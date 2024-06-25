#include "Obstacle.h"
#include "ImageUtil.h"
#include "FWM.h"
#include <cmath>

Obstacle::Obstacle(ObstacleType type, GLfloat R, GLfloat G, GLfloat B){
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


	ShapeType = static_cast<int>(type);

	SetColor(R, G, B);
}

void Obstacle::SetMoveSpeed(GLfloat Speed) {
	MoveSpeed = Speed;
}

void Obstacle::Update(float FT) {
	InitTransform();

	auto player = fw.Find("player", SearchRange::One, Layer::L2);
	if (player) Rotation = player->GetRotation();

	
	if (Size <= 0.75)
		Size -= FT * MoveSpeed * 2 * Size;
	else
		Size -= FT * MoveSpeed * Size;


	if (Size <= 0.65) {
		// �÷��̾��� ������ ���� ��� ����
		if (CheckShapeType()) {
			fw.AddObject(new FeedBack, "feedback", Layer::L1);
			fw.DeleteSelf(this);
		}

		// �÷��̾��� ������ �ٰ����� ������ �ٸ� ��� ���� �����⸦ �����ϰ� ��� ������ ������Ʈ�� �����
		// �÷��̾��� ȸ���� �����
		else{
			for (int i = 0; i < fw.Size(Layer::L1); ++i) {
				auto shape = fw.Find("obstacle", Layer::L1, i);
				if (shape) shape->SetMoveSpeed(0.0);
			}
			if (player) {
				player->SetRotateSpeed(0.0);
				player->SetGameOver();
			}

			if (!B_ObstacleAdded) {
				fw.DeleteObject("obstacle_generator", DeleteRange::One, SearchRange::One, Layer::L1);
				fw.AddObject(new BlinkingObstacle(ShapeType, ObjectColor.r, ObjectColor.g, ObjectColor.b, Rotation, Size), "b_obstacle", Layer::L2);
				B_ObstacleAdded = true;
			}
		}
	}

	Scale(Size, Size );
	Rotate(Rotation + 30);
}

bool Obstacle::CheckShapeType() {
	auto player = fw.Find("player", SearchRange::One, Layer::L2);
	if (player && player->GetShapeState() != ShapeType)
		return false;

	return true;
}

void Obstacle::Render() {
	ProcessTransform();
	imageUtil.Draw(Image);
}