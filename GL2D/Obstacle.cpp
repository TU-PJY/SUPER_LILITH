#include "Obstacle.h"
#include "ImageUtil.h"
#include "FWM.h"
#include "SoundUtil.h"
#include "CameraUtil.h"
#include <cmath>
#include <string>

Obstacle::Obstacle(ObstacleType type, GLfloat R, GLfloat G, GLfloat B){
	std::string TypeName;
	auto score = fw.Find("game_score");

	// 40�� ���ĺ��ʹ� �پ��� ������ �����Ѵ�
	switch (type) {
	case ObstacleType::Triangle:
		{
		if (score) {
			if (score->GetTime() < 40)
				TypeName = "obstacle_triangle_1";
			else {
				std::uniform_int_distribution uid{ 1, 4 };
				TypeName = "obstacle_triangle_";
				TypeName += std::to_string(uid(rd));
			}
		}
		}
		break;

	case ObstacleType::Square:
		{
		if (score) {
			if (score->GetTime() < 40)
				TypeName = "obstacle_square_1";
			else {
				std::uniform_int_distribution uid{ 1, 5 };
				TypeName = "obstacle_square_";
				TypeName += std::to_string(uid(rd));
			}
		}
		}
		break;

	case ObstacleType::Pentagon:
		{
		if (score) {
			if (score->GetTime() < 40)
				TypeName = "obstacle_pentagon_1";
			else {
				std::uniform_int_distribution uid{ 1, 5 };
				TypeName = "obstacle_pentagon_";
				TypeName += std::to_string(uid(rd));
			}
		}
		}
		break;
	}

	Image = imageUtil.SetImage(TypeName);
	ShapeType = static_cast<int>(type);

	SetColor(R, G, B);
}

void Obstacle::SetMoveSpeed(GLfloat Speed) {
	MoveSpeed = Speed;
}

void Obstacle::Update(float FT) {
	InitTransform();

	auto player = fw.Find("player");
	if (player) Rotation = player->GetRotation();

	auto score = fw.Find("game_score");
	if (score) {
		if (score->GetTime() >= 20 && score->GetTime() < 40) {
			if (MoveSpeed < 11) {
				MoveSpeed += FT * 0.1;
				if (MoveSpeed >= 11)
					MoveSpeed = 11;
			}
		}
		else if (score->GetTime() >= 40 && score->GetTime() < 60) {
			if (MoveSpeed < 12) {
				MoveSpeed += FT * 0.1;
				if (MoveSpeed >= 12)
					MoveSpeed = 12;
			}
		}
		else if (score->GetTime() >= 60 && score->GetTime() < 80) {
			if (MoveSpeed < 13) {
				MoveSpeed += FT * 0.1;
				if (MoveSpeed >= 13)
					MoveSpeed = 13;
			}
		}
		else if (score->GetTime() >= 80 && score->GetTime() < 100) {
			if (MoveSpeed < 15) {
				MoveSpeed += FT * 0.1;
				if (MoveSpeed >= 14)
					MoveSpeed = 14;
			}
		}
		else if (score->GetTime() >= 100) {
			if (MoveSpeed < 18) {
				MoveSpeed += FT * 0.1;
				if (MoveSpeed >= 18)
					MoveSpeed = 18;
			}
		}
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
	}
	
	if (Size <= 0.85 && Size > 0.75)
		Size -= FT * MoveSpeed * 2 * Size;

	else if (Size <= 0.75) {
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

	else
		Size -= FT * MoveSpeed * Size;

	Scale(Size, Size );
	Rotate(Rotation + ShapeRotation + 30);
}

bool Obstacle::CheckShapeType() {
	auto player = fw.Find("player");
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

	auto player = fw.Find("player");
	if (player) player->SetGameOver();

	if (!B_ObstacleAdded) {
		fw.DeleteObject("obstacle_generator", DeleteRange::One);
		fw.AddObject(new BlinkingObstacle, "b_obstacle", Layer::L1);

		B_ObstacleAdded = true;
	}

	SlowMusic(FT);
	ShakeCamera(FT);
}