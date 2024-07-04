#include "ObstacleGenerator.h"
#include "Obstacle.h"
#include "FWM.h"
#include <random>
#include <cmath>

void ObstacleGenerator::SetGenTime(GLfloat TimeValue) {
	GenTimeValue = TimeValue;
}

void ObstacleGenerator::Stop() {
	MulValue = 0.0;
}

void ObstacleGenerator::Update(float FT) {
	auto player = fw.Find("player");
	if(player) MulValue = player->GetMulValue();

	GenTimer += FT * 10 * MulValue;

	if (GenTimer >= GenTimeValue) {
		// 맨 처음 도형은 무조건 삼각형
		if (PrevType == -1)
			RandomType = 0;
		else
			GenerateShape();

		PrevType = RandomType;

		fw.AddObject(new Obstacle(static_cast<ObstacleType>(RandomType), 1.0, 1.0, 1.0), "obstacle", Layer::L1);

		// 생성 시간 오차 보정
		GLfloat DiffTime = GenTimeValue - GenTimer;

		GenTimer = 0;
		GenTimer += DiffTime;
	}

	auto score = fw.Find("game_score");
	if (score) {
		int Diff = score->GetDiff();
		if (Diff < 20)
			GenTimeValue = 10;

		else if (20 <= Diff && Diff < 60)
			GenTimeValue = 7;

		else if(60 <= Diff && Diff < 100)
			GenTimeValue = 4.5;

		else if (100 <= Diff && Diff < 140)
			GenTimeValue = 3.5;

		else if (140 <= Diff)
			GenTimeValue = 3;
	}
}

void ObstacleGenerator::GenerateShape() {
	auto score = fw.Find("game_score");
	if (score) {
		std::uniform_int_distribution uid{ 0, 2 };
		RandomType = uid(rd);
	}

	if (abs(RandomType - PrevType) > 1) {
		if (RandomType == 0)
			RandomType += 1;
		else
			RandomType -= 1;
	}

	// 이전 도형과 같은 도형일 경우 카운트 증가
	if (RandomType == PrevType)
		++SameCount;

	// 같은 도형이 2번 이상 나타나면 다른 도형으로 바꾼다 - 과한 중복 방지
	if (SameCount == 2) {
		// 삼각형 또는 오각형일 경우 범위 바깥으로 벗어나지 않도록 한다
		if (RandomType == 0)
			RandomType += 1;

		else if (RandomType == 2)
			RandomType -= 1;

		// 사각형일 경우 50퍼센트의 확률로 이전 도형 또는 다음 도형으로 바꾼다
		else {
			std::uniform_int_distribution uid{ 0, 1 };
			int rand = uid(rd);

			if (rand == 1)
				RandomType += 1;
			else
				RandomType -= 1;
		}

		SameCount = 0;
	}
}
