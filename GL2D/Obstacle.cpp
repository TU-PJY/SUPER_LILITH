#include "Obstacle.h"
#include "ImageUtil.h"
#include "FWM.h"
#include "SoundUtil.h"
#include "CameraUtil.h"
#include <cmath>
#include <random>

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

	auto score = fw.Find("game_score", SearchRange::One, Layer::L3);
	if (score) {
		if (score->GetTime() >= 20) {
			MoveSpeed += FT * 0.1;
			if (MoveSpeed >= 11)
				MoveSpeed = 11;
		}

		if (score->GetTime() >= 40) {
			MoveSpeed += FT * 0.1;
			if (MoveSpeed >= 12)
				MoveSpeed = 12;
		}

		if (score->GetTime() >= 60) {
			MoveSpeed += FT * 0.1;
			if (MoveSpeed >= 13)
				MoveSpeed = 13;
		}

		if (score->GetTime() >= 80) {
			MoveSpeed += FT * 0.1;
			if (MoveSpeed >= 14)
				MoveSpeed = 14;
		}
	}
	
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
		else
			ProcessGameOver(FT);
	}

	switch (ShapeType) {
	case 0:
		ShapeRotation = std::lerp(ShapeRotation, 0.0, FT * 15);
		break;
	case 1:
		ShapeRotation = std::lerp(ShapeRotation, -120, FT * 15);
		break;
	case 2:
		ShapeRotation = std::lerp(ShapeRotation, -192, FT * 15);
		break;
	case 3:
		ShapeRotation = std::lerp(ShapeRotation, -240, FT * 15);
		break;
	}

	Scale(Size, Size );
	Rotate(Rotation + ShapeRotation + 30);
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

void Obstacle::SlowMusic(float FT) {
	PlaySpeed -= FT;
	if (PlaySpeed <= 0)
		PlaySpeed = 0;

	soundUtil.SetPlaySpeed("ch_bgm", PlaySpeed);
}

void Obstacle::ShakeCamera(float FT) {

	ShakeValue -= FT * 0.1;
	if (ShakeValue <= 0)
		ShakeValue = 0;

	std::random_device rd;
	std::uniform_real_distribution urdX{ -ShakeValue, ShakeValue };
	std::uniform_real_distribution urdY{ -ShakeValue, ShakeValue };

	cam.ShakeValueX = urdX(rd);
	cam.ShakeValueY = urdY(rd);
}

void Obstacle::ProcessGameOver(float FT) {
	for (int i = 0; i < fw.Size(Layer::L1); ++i) {
		auto shape = fw.Find("obstacle", Layer::L1, i);
		if (shape) shape->SetMoveSpeed(0.0);
	}
	auto player = fw.Find("player", SearchRange::One, Layer::L2);
	if (player) player->SetGameOver();

	if (!B_ObstacleAdded) {
		fw.DeleteObject("obstacle_generator", DeleteRange::One, SearchRange::One, Layer::L1);
		fw.AddObject(new BlinkingObstacle, "b_obstacle", Layer::L1);
		B_ObstacleAdded = true;
	}

	SlowMusic(FT);
	ShakeCamera(FT);
}