#include "Button.h"
#include "Title.h"
#include "ImageUtil.h"
#include "MouseUtil.h"
#include "CameraUtil.h"
#include "FWM.h"
#include <cmath>

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
	if (aabb[0].CheckCollisionDot(DivideZoom(ASP(mouse.x), cam.Zoom), DivideZoom(mouse.y, cam.Zoom)))
		RightArrowSize = std::lerp(RightArrowSize, 0.35, FT * 15);
	else
		RightArrowSize = std::lerp(RightArrowSize, 0.3, FT * 15);

	// left arrow
	if (aabb[1].CheckCollisionDot(DivideZoom(ASP(mouse.x), cam.Zoom), DivideZoom(mouse.y, cam.Zoom)))
		LeftArrowSize = std::lerp(LeftArrowSize, 0.35, FT * 15);
	else
		LeftArrowSize = std::lerp(LeftArrowSize, 0.3, FT * 15);

	// button info
	if (aabb[2].CheckCollisionDot(DivideZoom(ASP(mouse.x), cam.Zoom), DivideZoom(mouse.y, cam.Zoom)))
		ButtonInfoSize = std::lerp(ButtonInfoSize, 0.23, FT * 15);
	else
		ButtonInfoSize = std::lerp(ButtonInfoSize, 0.2, FT * 15);

	// button sound
	if (aabb[3].CheckCollisionDot(DivideZoom(ASP(mouse.x), cam.Zoom), DivideZoom(mouse.y, cam.Zoom)))
		ButtonSoundSize = std::lerp(ButtonSoundSize, 0.23, FT * 15);
	else
		ButtonSoundSize = std::lerp(ButtonSoundSize, 0.2, FT * 15);
}

void Button::Render() {
	InitTransform();
	Translate(DivideZoom(rect.rx - 0.18, cam.Zoom), 0.0);
	ScaleSpot(DivideZoom(RightArrowSize, cam.Zoom), DivideZoom(RightArrowSize, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(ArrowRight);

	InitTransform();
	Translate(DivideZoom(rect.lx + 0.18, cam.Zoom), 0.0);
	ScaleSpot(DivideZoom(LeftArrowSize, cam.Zoom), DivideZoom(LeftArrowSize, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(ArrowLeft);

	InitTransform();
	Translate(DivideZoom(rect.rx - 0.15, cam.Zoom), DivideZoom(rect.ly + 0.15, cam.Zoom));
	ScaleSpot(DivideZoom(ButtonInfoSize, cam.Zoom), DivideZoom(ButtonInfoSize, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(ButtonInfo);

	InitTransform();
	Translate(DivideZoom(rect.rx - 0.4, cam.Zoom), DivideZoom(rect.ly + 0.15, cam.Zoom));
	ScaleSpot(DivideZoom(ButtonSoundSize, cam.Zoom), DivideZoom(ButtonSoundSize, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(ButtonSoundEnable);

	aabb[0].Update(DivideZoom(rect.rx - 0.18, cam.Zoom), 0.0, DivideZoom(0.25, cam.Zoom), DivideZoom(0.25, cam.Zoom));
	aabb[1].Update(DivideZoom(rect.lx + 0.18, cam.Zoom), 0.0, DivideZoom(0.25, cam.Zoom), DivideZoom(0.25, cam.Zoom));
	aabb[2].Update(DivideZoom(rect.rx - 0.15, cam.Zoom), DivideZoom(rect.ly + 0.15, cam.Zoom), DivideZoom(0.2, cam.Zoom), DivideZoom(0.2, cam.Zoom));
	aabb[3].Update(DivideZoom(rect.rx - 0.4, cam.Zoom), DivideZoom(rect.ly + 0.15, cam.Zoom), DivideZoom(0.2, cam.Zoom), DivideZoom(0.2, cam.Zoom));
}

void Button::ClickButton() {
	// right arrow
	if (aabb[0].CheckCollisionDot(DivideZoom(ASP(mouse.x), cam.Zoom), DivideZoom(mouse.y, cam.Zoom))) {
		auto title = fw.Find("title", SearchRange::One, Layer::L2);
		if (title) title->ChangeLobbyPage(1);
	}

	// left arrow
	if (aabb[1].CheckCollisionDot(DivideZoom(ASP(mouse.x), cam.Zoom), DivideZoom(mouse.y, cam.Zoom))) {
		auto title = fw.Find("title", SearchRange::One, Layer::L2);
		if (title) title->ChangeLobbyPage(0);
	}
}