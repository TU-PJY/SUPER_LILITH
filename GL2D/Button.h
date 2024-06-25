#pragma once
#include "ObjectBase.h"
#include "CollisionUtil.h"
#include <array>

class Button : public OBJ_BASE {
private:
	unsigned int ArrowRight{}, ArrowLeft{}, ButtonInfo{}, ButtonSoundEnable{}, ButtonSoundDisable{};

	GLfloat RightArrowSize{0.3}, LeftArrowSize{0.3};
	GLfloat ButtonInfoSize{ 0.2 }, ButtonSoundSize{ 0.2 };

	AABB aabb[4];

public:
	Button();
	void Update(float FT);
	void ClickButton();
	void Render();
};

