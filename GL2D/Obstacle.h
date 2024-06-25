#pragma once
#include "ObjectBase.h"

enum class ObstacleType 
{Triangle, Square, Pentagon, Hexagon};

class Obstacle : public OBJ_BASE {
private:
	unsigned int Image{};
	int ShapeType{};
	GLfloat Size = 15;
	GLfloat Rotation{};
	GLfloat MoveSpeed = 1.5;
	bool Checked{};

public:
	Obstacle(ObstacleType type);
	void SetMoveSpeed(GLfloat Speed);
	void Update(float FT);
	bool CheckShapeType();
	void Render();
};

