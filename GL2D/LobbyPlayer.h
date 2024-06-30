#pragma once
#include "ObjectBase.h"
#include "ImageUtil.h"
#include <random>
#include <array>

class LobbyPlayer : public OBJ_BASE {
private:
	std::array<unsigned int, 7> Image{};
	
	GLfloat BlinkTimer{};
	GLfloat NextTime{};
	int BlinkCount{};
	int NextIndex{};
	bool BlinkState{};
	std::random_device rd;
	
public:
	LobbyPlayer() {
		Image[0] = imageUtil.SetImage("lilith_body_1");
		Image[1] = imageUtil.SetImage("lilith_body_2");
		Image[2] = imageUtil.SetImage("lilith_body_3");
		Image[3] = imageUtil.SetImage("lilith_body_4");
		Image[4] = imageUtil.SetImage("lilith_body_5");
		Image[5] = imageUtil.SetImage("lilith_body_6");
		Image[6] = imageUtil.SetImage("lilith_body_7");

		Translate(0.0, -0.3);
		ScaleSpot(1.2, 1.2);
	}

	void Update(float FT) {
		InitTransform();
		Translate(0.0, -0.3);
		ScaleSpot(1.2, 1.2);

		BlinkTimer += FT * 10;

		if (BlinkTimer >= NextTime && !BlinkState) {
			++BlinkCount;

			BlinkState = true;
			BlinkTimer = 0;
		}

		if (BlinkTimer >= 2 && BlinkState) {
			std::uniform_int_distribution uid{ 10, 30 };
			std::uniform_int_distribution uid_index{ 1, 6 };
			NextTime = uid(rd);
			NextIndex = uid_index(rd);

			BlinkState = false;
			BlinkTimer = 0;
		}
	}

	void Render() {
		ProcessTransform();
		if(BlinkState)
			imageUtil.Draw(Image[NextIndex]);
		else
			imageUtil.Draw(Image[0]);
	}
};

