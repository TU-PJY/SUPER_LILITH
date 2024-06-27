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
		// �� ó�� ������ ������ �ﰢ��
		if (PrevType == -1)
			RandomType = 0;
		else
			GenerateShape();

		PrevType = RandomType;

		fw.AddObject(new Obstacle(static_cast<ObstacleType>(RandomType), 1.0, 1.0, 1.0), "obstacle", Layer::L1);

		// ���� �ð� ���� ����
		GLfloat DiffTime = GenTimeValue - GenTimer;

		GenTimer = 0;
		GenTimer += DiffTime;
	}

	auto score = fw.Find("game_score");
	if (score) {
		if (score->GetTime() >= 20 && score->GetTime() < 40)
			GenTimeValue = 8;

		/*else if (score->GetTime() >= 40 && score->GetTime() < 60)
			GenTimeValue = 6;*/

		else if (score->GetTime() >= 60 && score->GetTime() < 80)
			GenTimeValue = 6;

		else if (score->GetTime() >= 80 && score->GetTime() < 100)
			GenTimeValue = 5;

		else if (score->GetTime() >= 100)
			GenTimeValue = 4;
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

	// ���� ������ ���� ������ ��� ī��Ʈ ����
	if (RandomType == PrevType)
		++SameCount;

	// ���� ������ 2�� �̻� ��Ÿ���� �ٸ� �������� �ٲ۴� - ���� �ߺ� ����
	if (SameCount == 2) {
		// �ﰢ�� �Ǵ� �������� ��� ���� �ٱ����� ����� �ʵ��� �Ѵ�
		if (RandomType == 0)
			RandomType += 1;

		else if (RandomType == 2)
			RandomType -= 1;

		// �簢���� ��� 50�ۼ�Ʈ�� Ȯ���� ���� ���� �Ǵ� ���� �������� �ٲ۴�
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
