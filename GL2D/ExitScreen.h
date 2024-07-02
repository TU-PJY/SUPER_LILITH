#pragma once
#include "FWM.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "CameraUtil.h"
#include "TextUtil.h"

class ExitScreen : public OBJ_BASE {
private:
	unsigned int BackImage{};
	TextUtil Text;

public:
	ExitScreen() {
		Text.Init(L"열정그자체", FW_NORMAL, TRUE);
		Text.SetAlign(Align::Middle);
		BackImage = imageUtil.SetImage("black_front");
		Scale(ASP(10.0), 10.0);
		AlphaValue = 0.5;
	}

	void Update(float FT) {
		InitTransform();
		Scale(ASP(10.0), 10.0);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(BackImage);

		Text.Draw(0.0, 0.5, 0.5, "EXIT?");
		Text.Draw(rect.lx + 0.5, 0.0, 0.3, "NO");
		Text.Draw(rect.rx - 0.5, 0.0, 0.3, "YES");
	}
};
