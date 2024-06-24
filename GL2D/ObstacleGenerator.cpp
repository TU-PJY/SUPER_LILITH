#include "ObstacleGenerator.h"
#include "Obstacle.h"
#include "FWM.h"
#include <random>

std::random_device rd;
std::uniform_int_distribution uid{ 0, 3 };

void ObstacleGenerator::SetGenTime(GLfloat TimeValue) {
	GenTimeValue = TimeValue;
}

void ObstacleGenerator::Update(float FT) {
	GenTimer += FT * 10;

	if (GenTimer >= GenTimeValue) {
		fw.AddObject(new Obstacle(static_cast<ObstacleType>(uid(rd))), "obstacle", Layer::L1);
		GenTimer = 0;
	}
}
