#pragma once
#include "ObjectBase.h"
#include "TextUtil.h"

class GameScore : public OBJ_BASE {
private:
	int Second{};
	float MiliSecond{};
	unsigned int ScorePlate{};

	TextUtil Text;

public:
	GameScore();
	void Update(float FT);
	void Render();
	void SaveHighScoreToFile();
};