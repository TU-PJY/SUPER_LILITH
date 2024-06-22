#pragma once
#include "TextUtil.h"

class AABB {
private:
	glm::mat4 TranslateMatrix{ 1.0f }, RotateMatrix{ 1.0f }, ScaleMatrix{ 1.0f };
	unsigned int ModelLocation{}, TransparencyLocation{}, ObjectColorLocation{};

	GLfloat LeftX{}, LeftY{};
	GLfloat RightX{}, RightY{};

	unsigned int Box{};
	TextUtil text;

public:
	void Init();
	void Update(GLfloat X, GLfloat Y, GLfloat xScale, GLfloat yScale, bool UseViewportPosition = false);
	bool CheckCollisionAABB(AABB aabb);
	bool CheckCollisionDot(GLfloat X, GLfloat Y);
	void InitTransform();
	void ProcessTransform();
};