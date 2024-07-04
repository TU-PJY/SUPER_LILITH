#include "ObjectBase.h"
#include <random>

#pragma once
class ObstacleGenerator : public OBJ_BASE {
private:
	GLfloat GenTimer{};
	GLfloat GenTimeValue = 10;
	int PrevType{-1}, RandomType{};
	int SameCount{};
	std::random_device rd;

	GLfloat MulValue{};

public:
	void SetGenTime(GLfloat TimeValue);
	void Stop();
	void Update(float FT);
	void GenerateShape();
};

