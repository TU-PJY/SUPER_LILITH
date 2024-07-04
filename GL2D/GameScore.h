#pragma once
#include "ObjectBase.h"
#include "TextUtil.h"

enum DiffType
{Easy, Normal, Hard, Harder, Insane};

class GameScore : public OBJ_BASE {
private:
	float TimeElapsed{0};
	float Diff{};
	unsigned int ScorePlate{};
	bool StopState{};

	TextUtil Text;

	GLfloat MulValue{};

	int HighSec{}, HighMil{};
	bool HighScore{};

public:
	GameScore();
	float GetDiff();
	void Stop();
	void Update(float FT);
	void Render();
	void SaveHighScoreToFile();
	float GetTime();
};