#include "ObjectBase.h"

#pragma once
class ObstacleGenerator : public OBJ_BASE {
private:
	GLfloat GenTimer{};
	GLfloat GenTimeValue = 10;
	int PrevType{-1}, RandomType{};

public:
	void SetGenTime(GLfloat TimeValue);
	void Update(float FT);
};

