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

public:
	void SetGenTime(GLfloat TimeValue);
	void Update(float FT);
	void GenerateShape();
};

