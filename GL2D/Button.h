#pragma once
#include "ObjectBase.h"
#include "TextUtil.h"
#include <array>

class Button : public OBJ_BASE {
private:
	unsigned int ArrowRight{}, ArrowLeft{}, ButtonInfo{}, ButtonEffectOn{}, ButtonEffectOff{}, ButtonMusicReset{}, ButtonMusicResume{};
	unsigned int ButtonDataReset{};
	GLfloat RightArrowSize{0.3}, LeftArrowSize{0.3};
	GLfloat ButtonInfoSize{ 0.2 }, ButtonSoundSize{ 0.2 };

	bool StartAnimation{};

	GLfloat ArrowMovePosition = 0.5;
	GLfloat ButtonMovePosition = 0.5;

	bool RenderLeft{true}, RenderRight{true};

	TextUtil Text;

public:
	Button();
	void EnableStartAnimation();
	void Update(float FT);
	void Render();
	void InputKey(unsigned char KEY, bool KeyDown);
};