#pragma once
#include "ObjectBase.h"

enum class ObstacleType 
{Triangle, Square, Pentagon, Hexagon};

class Obstacle : public OBJ_BASE {
private:
	unsigned int Image{};
	ObstacleType type{};
	GLfloat Size = 11;
	GLfloat Rotation{};
	GLfloat MoveSpeed = 3;

public:
	Obstacle(ObstacleType type);
	void Update(float FT);
	void Render();
};

