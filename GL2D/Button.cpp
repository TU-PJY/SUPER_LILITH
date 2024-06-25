#include "Button.h"
#include "ImageUtil.h"
#include "MouseUtil.h"
#include "Title.h"
#include "FWM.h"
#include <cmath>

enum Dir
{PageLeft, PageRight};

Button::Button() {
	ArrowRight = imageUtil.SetImage("arrow_right");
	ArrowLeft = imageUtil.SetImage("arrow_left");
	ButtonInfo = imageUtil.SetImage("button_info");
	ButtonSoundEnable = imageUtil.SetImage("button_sound_enable");
	ButtonSoundDisable = imageUtil.SetImage("button_sound_disable");

	SetColor(1.0, 1.0, 1.0);
	
	for(int i = 0; i < 4; ++i)
		aabb[i].Init();
}

void Button::Update(float FT) {
	// right arrow
	if (aabb[0].CheckCollisionDot(ASP(mouse.x), mouse.y))
		RightArrowSize = std::lerp(RightArrowSize, 0.35, FT * 15);
	else
		RightArrowSize = std::lerp(RightArrowSize, 0.3, FT * 15);

	// left arrow
	if (aabb[1].CheckCollisionDot(ASP(mouse.x), mouse.y))
		LeftArrowSize = std::lerp(LeftArrowSize, 0.35, FT * 15);
	else
		LeftArrowSize = std::lerp(LeftArrowSize, 0.3, FT * 15);

	// button info
	if (aabb[2].CheckCollisionDot(ASP(mouse.x), mouse.y))
		ButtonInfoSize = std::lerp(ButtonInfoSize, 0.23, FT * 15);
	else
		ButtonInfoSize = std::lerp(ButtonInfoSize, 0.2, FT * 15);

	// button sound
	if (aabb[3].CheckCollisionDot(ASP(mouse.x), mouse.y))
		ButtonSoundSize = std::lerp(ButtonSoundSize, 0.23, FT * 15);
	else
		ButtonSoundSize = std::lerp(ButtonSoundSize, 0.2, FT * 15);
}

void Button::Render() {
	InitTransform();
	Translate(rect.rx - 0.18, 0.0);
	ScaleSpot(RightArrowSize, RightArrowSize);
	ProcessTransform();
	imageUtil.Draw(ArrowRight);

	InitTransform();
	Translate(rect.lx + 0.18, 0.0);
	ScaleSpot(LeftArrowSize, LeftArrowSize);
	ProcessTransform();
	imageUtil.Draw(ArrowLeft);

	InitTransform();
	Translate(rect.rx - 0.15, rect.ly + 0.15);
	ScaleSpot(ButtonInfoSize, ButtonInfoSize);
	ProcessTransform();
	imageUtil.Draw(ButtonInfo);

	InitTransform();
	Translate(rect.rx - 0.4, rect.ly + 0.15);
	ScaleSpot(ButtonSoundSize, ButtonSoundSize);
	ProcessTransform();
	imageUtil.Draw(ButtonSoundEnable);

	aabb[0].Update(rect.rx - 0.18, 0.0, 0.25, 0.25);
	aabb[1].Update(rect.lx + 0.18, 0.0, 0.25, 0.25);
	aabb[2].Update(rect.rx - 0.15, rect.ly + 0.15, 0.2, 0.2);
	aabb[3].Update(rect.rx - 0.4, rect.ly + 0.15, 0.2, 0.2);
}

void Button::ClickButton() {
	// right arrow
	if (aabb[0].CheckCollisionDot(ASP(mouse.x), mouse.y)) {
		auto title = fw.Find("title", SearchRange::One, Layer::L2);
		if (title) title->ChangeLobbyPage(PageRight);
	}

	// left arrow
	if (aabb[1].CheckCollisionDot(ASP(mouse.x), mouse.y)) {
		auto title = fw.Find("title", SearchRange::One, Layer::L2);
		if (title) title->ChangeLobbyPage(PageLeft);
	}
}