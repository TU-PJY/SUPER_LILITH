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
	int num{};

	switch (type) {
	case ObstacleType::Triangle:
	{
		std::uniform_int_distribution uid{ 1, 5 };
		num = uid(rd);
		if (num == 5)
			DirectionChanger = true;

		TypeName = "obstacle_triangle_";
		ShapeRotation = 0.0;
	}
		break;

	case ObstacleType::Square:
	{
		std::uniform_int_distribution uid{ 1, 7 };
		num = uid(rd);
		if (num == 7)
			DirectionChanger = true;

		TypeName = "obstacle_square_";
		ShapeRotation = -90.0;
	}
		break;

	case ObstacleType::Pentagon:
	{
		std::uniform_int_distribution uid{ 1, 7 };
		num = uid(rd);
		if (num == 7)
			DirectionChanger = true;

		TypeName = "obstacle_pentagon_";
		ShapeRotation = -192.0;
	}
		break;
	}

	if (score && score->GetDiff() < 20) {
		num = 1;
		DirectionChanger = false;
	}

	TypeName += std::to_string(num);

	Image = imageUtil.SetImage(TypeName);
	ShapeType = static_cast<int>(type);

	SetColor(R, G, B);
	Rotate(ShapeRotation);
	IsMove = true;
}

void Obstacle::Stop() {
	IsMove = false;
	MoveSpeed = 0;
}

void Obstacle::Update(float FT) {
	InitTransform();

	auto player = fw.Find("player");
	if (player) Rotation = player->GetRotation();

	if (IsMove) {
		auto score = fw.Find("game_score");
		if (score) {
			int Diff = score->GetDiff();

			if (Diff < 20)
				MoveSpeed = 1.6;

			else if (20 <= Diff && Diff < 60)
				MoveSpeed = 1.8;

			else if (60 <= Diff && Diff < 100)
				MoveSpeed = 2.0;

			else if (100 <= Diff && Diff < 140)
				MoveSpeed = 2.2;

			else if (140 <= Diff)
				MoveSpeed = 2.4;
		}
	}
	
	if (Size <= 0.85 && Size > 0.75)
		Size -= FT * MoveSpeed * 2 * Size;

	else if (Size <= 0.75) {
		// 플레이어의 도형과 같을 경우 삭제
		if (CheckShapeType()) {
			if (DirectionChanger) {
				fw.Find("player");
				if (player) player->ChangeRotationDirection();
			}

			fw.AddObject(new FeedBack, "feedback", Layer::L1);
			fw.DeleteSelf(this);
		}

		// 플레이어의 도형이 다가오는 도형과 다를 경우 도형 생성기를 삭제하고 모든 도형의 업데이트가 멈춘다
		// 플레이어의 회전도 멈춘다
		else
			ProcessGameOver(FT);
	}

	else
		Size -= FT * MoveSpeed * Size;

	Scale(Size, Size );
	Rotate(Rotation + ShapeRotation);
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
		if (shape) shape->Stop();
	}

	auto player = fw.Find("player");
	if (player) player->SetGameOver();

	auto score = fw.Find("game_score");
	if (score) score->Stop();

	if (!B_ObstacleAdded) {
		fw.DeleteObject("obstacle_generator", DeleteRange::One);
		fw.AddObject(new BlinkingObstacle, "b_obstacle", Layer::L1);

		B_ObstacleAdded = true;
	}

	SlowMusic(FT);
	ShakeCamera(FT);
}