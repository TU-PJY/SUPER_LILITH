#pragma once
#include "FWM.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "DataUtil.h"
#include <cmath>

enum State
{Arrow, Shift};

class ControlTut : public OBJ_BASE {
private:
	unsigned int ImageArrowRight{}, ImageArrowLeft{}, ImageShiftRight{}, ImageShiftLeft{};
	GLfloat Frame{};
	GLfloat Size = 0.2;
	GLfloat SizeRight{0.2}, SizeLeft{0.2};
	GLfloat SizeRightDest{ 0.2 }, SizeLeftDest{0.2};

	GLfloat AlphaArrow = 0.0;
	GLfloat AlphaShift = 0.0;
	int RenderState = Arrow;

public:
	ControlTut() {
		ImageArrowRight = imageUtil.SetImage("control_tut_right");
		ImageArrowLeft = imageUtil.SetImage("control_tut_left");
		ImageShiftRight = imageUtil.SetImage("control_tut_rshift");
		ImageShiftLeft = imageUtil.SetImage("control_tut_lshift");

		dataUtil.WriteData("Play Once", 1);

		AlphaValue = 0.0;
	}

	void Update(float FT) {
		Frame += FT * 2;

		if (Frame >= 8)
			RenderState = Shift;

		SizeRightDest = ((int)Frame % 2) * 0.03;
		SizeLeftDest = -((int)Frame % 2) * 0.03;

		SizeRight = std::lerp(SizeRight, SizeRightDest, FT * 10);
		SizeLeft = std::lerp(SizeLeft, SizeLeftDest, FT * 10);

		if (RenderState == Arrow && Frame < 8)
			AlphaArrow = std::lerp(AlphaArrow, 1.0, FT * 5);

		if (RenderState == Shift && Frame < 16) {
			AlphaArrow = std::lerp(AlphaArrow, 0.0, FT * 10);
			AlphaShift = std::lerp(AlphaShift, 1.0, FT * 10);
		}

		if (Frame >= 16) {
			AlphaShift = std::lerp(AlphaShift, 0.0, FT * 10);
			if (AlphaShift <= 0.001)
				fw.DeleteSelf(this);
		}
	}

	void Render() {
		if (RenderState == Arrow) {
			SetAlpha(AlphaArrow);

			InitTransform();
			Translate(0.6, 0.0);
			ScaleSpot(Size + SizeRight, Size + SizeRight);
			ProcessTransform();
			imageUtil.Draw(ImageArrowRight);

			InitTransform();
			Translate(-0.6, 0.0);
			ScaleSpot(Size + SizeLeft, Size + SizeLeft);
			ProcessTransform();
			imageUtil.Draw(ImageArrowLeft);
		}

		else if (RenderState == Shift) {
			SetAlpha(AlphaShift);

			InitTransform();
			Translate(0.6, 0.0);
			ScaleSpot(imageUtil.Aspect(300, 128) * (Size + SizeRight), Size + SizeRight);
			ProcessTransform();
			imageUtil.Draw(ImageShiftRight);

			InitTransform();
			Translate(-0.6, 0.0);
			ScaleSpot(imageUtil.Aspect(300, 128) * (Size + SizeLeft), Size + SizeLeft);
			ProcessTransform();
			imageUtil.Draw(ImageShiftLeft);
		}
	}
};