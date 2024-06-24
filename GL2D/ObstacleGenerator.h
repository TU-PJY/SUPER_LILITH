#include "ObjectBase.h"

#pragma once
class ObstacleGenerator : public OBJ_BASE {
private:
	GLfloat GenTimer{};
	GLfloat GenTimeValue = 15;

public:
	void SetGenTime(GLfloat TimeValue);
	void Update(float FT);
};

