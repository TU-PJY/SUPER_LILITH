#pragma once
#include "ImageUtil.h"
#include "ObjBase.h"
#include "FWM.h"

class BlackFront : public OBJ_BASE {
private:
	unsigned int Image{};

public:
	BlackFront() {
		Image = imageUtil.SetImage("black_front");
		AlphaValue = 0.5;
		Scale(ASP(10.0), 10.0);
	}

	void Update(float FT) {
		AlphaValue = std::lerp(AlphaValue, 0.0, FT * 10);
		if (AlphaValue <= 0.001)
			fw.DeleteSelf(this);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};
