#include "ObstacleGenerator.h"
#include "Obstacle.h"
#include "FWM.h"
#include <random>
#include <cmath>

std::random_device rd;
std::uniform_int_distribution uid{ 0, 3 };

void ObstacleGenerator::SetGenTime(GLfloat TimeValue) {
	GenTimeValue = TimeValue;
}

void ObstacleGenerator::Update(float FT) {
	GenTimer += FT * 10;

	if (GenTimer >= GenTimeValue) {
		if (PrevType == -1)
			RandomType = 0;

		else {
			RandomType = uid(rd);

			while (true) {
				RandomType = uid(rd);
				if (RandomType != PrevType && abs(RandomType - PrevType) <= 1)
					break;
			}
		}

		PrevType = RandomType;

		fw.AddObject(new Obstacle(static_cast<ObstacleType>(RandomType)), "obstacle", Layer::L1);

		GenTimer = 0;
	}
}
