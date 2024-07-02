#pragma once
#include "FWM.h"
#include "ObjectBase.h"
#include "ImageUtil.h"
#include <cmath>

class White : public OBJ_BASE {
private:
	unsigned int Image{};
	GLfloat Delay{};

public:
	White() {
		Image = imageUtil.SetImage("white_front");
		Scale(ASP(5.0), 5.0);
	}

	void Update(float FT) {
		Delay += FT * 10;

		if (Delay >= 2.5) {
			AlphaValue = std::lerp(AlphaValue, 0.0, FT * 5);
			if (AlphaValue <= 0.01)
				fw.DeleteSelf(this);
		}
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};