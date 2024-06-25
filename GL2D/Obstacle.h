#pragma once
#include "ObjectBase.h"

enum class ObstacleType 
{Triangle, Square, Pentagon, Hexagon};

class Obstacle : public OBJ_BASE {
private:
	unsigned int Image{};
	ObstacleType type{};
	GLfloat Size = 15;
	GLfloat Rotation{};
	GLfloat MoveSpeed = 1.5;

public:
	Obstacle(ObstacleType type);
	void Update(float FT);
	void Render();
};

