#include "ObstacleGenerator.h"
#include "Obstacle.h"
#include "FWM.h"
#include <random>
#include <cmath>

void ObstacleGenerator::SetGenTime(GLfloat TimeValue) {
	GenTimeValue = TimeValue;
}

void ObstacleGenerator::Update(float FT) {
	GenTimer += FT * 10;

	if (GenTimer >= GenTimeValue) {
		if (PrevType == -1)
			RandomType = 0;

		else {
			std::random_device rd;
			std::uniform_int_distribution uid{ 0, 3 };
			RandomType = uid(rd);

			while (true) {
				RandomType = uid(rd);
				if (abs(RandomType - PrevType) <= 1)
					break;
			}
		}

		PrevType = RandomType;

		fw.AddObject(new Obstacle(static_cast<ObstacleType>(RandomType), 1.0, 1.0, 1.0), "obstacle", Layer::L1);


		GLfloat DiffTime = GenTimeValue - GenTimer;

		GenTimer = 0;
		GenTimer += DiffTime;
	}

	auto score = fw.Find("game_score", SearchRange::One, Layer::L3);
	if (score) {
		if (score->GetTime() >= 20)
			GenTimeValue = 8;

		if (score->GetTime() >= 40)
			GenTimeValue = 6;

		if (score->GetTime() >= 60)
			GenTimeValue = 5;
	}
}
