#pragma once
#include "ObjectBase.h"
#include "TextUtil.h"

class GameScore : public OBJ_BASE {
private:
	float MiliSecond{};
	int Second{};
	unsigned int ScorePlate{};

	TextUtil Text;

public:
	GameScore();
	void Update(float FT);
	void Render();
	void SaveHighScoreToFile();
	float GetTime();
};