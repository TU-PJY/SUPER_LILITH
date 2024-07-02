#include "Button.h"
#include "Title.h"
#include "ImageUtil.h"
#include "MouseUtil.h"
#include "CameraUtil.h"
#include "MusicPlayer.h"
#include "FWM.h"
#include <cmath>

Button::Button() {
	ArrowRight = imageUtil.SetImage("arrow_right");
	ArrowLeft = imageUtil.SetImage("arrow_left");
	ButtonInfo = imageUtil.SetImage("button_info");
	ButtonSoundEnable = imageUtil.SetImage("button_sound_enable");
	ButtonSoundDisable = imageUtil.SetImage("button_sound_disable");

	Text.Init(L"열정그자체", FW_NORMAL, TRUE);
	Text.SetAlign(Align::Middle);
}

void Button::EnableStartAnimation() {
	StartAnimation = true;
}

void Button::Update(float FT) {
	auto title = fw.Find("title");
	if (title) ObjectColor = title->GetColorSet();

	Text.SetColor(ObjectColor.r, ObjectColor.g, ObjectColor.b);

	if (mp.MusicNumber == 1)
		RenderLeft = false;

	else if (mp.MusicNumber == mp.GetMusicNum())
		RenderRight = false;

	else {
		RenderLeft = true;
		RenderRight = true;
	}

	if (StartAnimation) {
		ArrowMovePosition = std::lerp(ArrowMovePosition, 0.5, FT * 5);
		ButtonMovePosition = std::lerp(ButtonMovePosition, 0.5, FT * 5);
	}

	else {
		ArrowMovePosition = std::lerp(ArrowMovePosition, 0.0, FT * 5);
		ButtonMovePosition = std::lerp(ButtonMovePosition, 0.0, FT * 5);
	}
}

void Button::Render() {
	if (RenderRight) {
		InitTransform();
		Translate(DivideZoom(rect.rx - 0.18, cam.Zoom), 0.0);
		Translate(DivideZoom(ArrowMovePosition, cam.Zoom), 0.0);
		ScaleSpot(DivideZoom(RightArrowSize, cam.Zoom), DivideZoom(RightArrowSize, cam.Zoom));
		ProcessTransform();
		imageUtil.Draw(ArrowRight);
	}

	if (RenderLeft) {
		InitTransform();
		Translate(DivideZoom(rect.lx + 0.18, cam.Zoom), 0.0);
		Translate(DivideZoom(-ArrowMovePosition, cam.Zoom), 0.0);
		ScaleSpot(DivideZoom(LeftArrowSize, cam.Zoom), DivideZoom(LeftArrowSize, cam.Zoom));
		ProcessTransform();
		imageUtil.Draw(ArrowLeft);
	}

	InitTransform();
	Translate(DivideZoom(rect.rx - 0.15, cam.Zoom), DivideZoom(rect.ly + 0.15, cam.Zoom));
	Translate(0.0, DivideZoom(-ButtonMovePosition, cam.Zoom));
	ScaleSpot(DivideZoom(ButtonInfoSize, cam.Zoom), DivideZoom(ButtonInfoSize, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(ButtonInfo);

	InitTransform();
	Translate(DivideZoom(rect.rx - 0.4, cam.Zoom), DivideZoom(rect.ly + 0.15, cam.Zoom));
	Translate(0.0, DivideZoom(-ButtonMovePosition, cam.Zoom));
	ScaleSpot(DivideZoom(ButtonSoundSize, cam.Zoom), DivideZoom(ButtonSoundSize, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(ButtonSoundEnable);

	Text.Draw(
		DivideZoom(rect.rx - 0.4, cam.Zoom), DivideZoom(rect.ly + 0.27 - ButtonMovePosition, cam.Zoom),
		DivideZoom(0.1, cam.Zoom), "1"
	);

	Text.Draw(
		DivideZoom(rect.rx - 0.15, cam.Zoom), DivideZoom(rect.ly + 0.27 - ButtonMovePosition, cam.Zoom),
		DivideZoom(0.1, cam.Zoom), "2"
	);
}