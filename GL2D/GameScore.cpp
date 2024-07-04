#include "GameScore.h"
#include "ImageUtil.h"
#include "DataUtil.h"
#include "CameraUtil.h"
#include "MusicPlayer.h"
#include "FWM.h"
#include <sstream>
#include <iomanip>

GameScore::GameScore() {
	Text.Init(L"Galiver Sans", FW_BOLD, TRUE);
	ScorePlate = imageUtil.SetImage("score_plate");

	Translate(rect.rx - 0.35, rect.ly + 0.14);
	ScaleSpot(0.3 * imageUtil.Aspect(350, 128), 0.3);

	// 선택한 난이도에 따라 시작 난이도가 달라진다
	int DiffValue = mp.MusicNumber - 1;

	switch (DiffValue) {
	case 0:  // easy
		Diff = 0;
		HighSec = dataUtil.LoadData("Easy Sec");
		HighMil = dataUtil.LoadData("Easy Mil");
		break;
	case 1:  // normal
		Diff = 20;
		HighSec = dataUtil.LoadData("Normal Sec");
		HighMil = dataUtil.LoadData("Normal Mil");
		break;
	case 2:  // hard
		Diff = 60;
		HighSec = dataUtil.LoadData("Hard Sec");
		HighMil = dataUtil.LoadData("Hard Mil");
		break;
	case 3:  // harder
		Diff = 100;
		HighSec = dataUtil.LoadData("Harder Sec");
		HighMil = dataUtil.LoadData("Harder Mil");
		break;
	case 4:  // insane
		Diff = 140;
		HighSec = dataUtil.LoadData("Insane Sec");
		HighMil = dataUtil.LoadData("Insane Mil");
		break;
	}
}

float GameScore::GetDiff() {
	return Diff;
}

void GameScore::Stop() {
	StopState = true;
}

void GameScore::Update(float FT) {
	auto player = fw.Find("player");
	if (player) MulValue = player->GetMulValue();

	if (!StopState) {
		TimeElapsed += FT * MulValue;
		Diff += FT * MulValue;
	}

}

void GameScore::Render() {
	if (fw.Mode() == "PlayMode") {
		InitTransform();
		Translate(rect.rx - 0.35 - cam.ShakeValueX, rect.ly + 0.18 - cam.ShakeValueY);
		ScaleSpot(0.3 * imageUtil.Aspect(400, 128), 0.4);
		ProcessTransform();
		imageUtil.Draw(ScorePlate);

		float RealTimeElpased = std::floor(TimeElapsed * std::pow(10, 1)) / std::pow(10, 1);

		if ((static_cast<int>(TimeElapsed) > HighSec) ||
			((static_cast<int>(RealTimeElpased * 10) % 10 > HighMil) && (static_cast<int>(TimeElapsed) == HighSec))) {
			HighScore = true;
		}

		if (HighScore) {
			Text.SetColor(0.0, 1.0, 0.0);

			Text.Draw(rect.rx - 0.75 - cam.ShakeValueX, rect.ly + 0.05 - cam.ShakeValueY, 0.2, "%.1f",
				std::floor(TimeElapsed * std::pow(10, 1)) / std::pow(10, 1));

			Text.Draw(rect.rx - 0.7 - cam.ShakeValueX,
				rect.ly + 0.25 - cam.ShakeValueY, 0.1, "HighScore: %.1f",
				std::floor(TimeElapsed * std::pow(10, 1)) / std::pow(10, 1));
		}

		else {
			Text.Draw(rect.rx - 0.75 - cam.ShakeValueX, rect.ly + 0.05 - cam.ShakeValueY, 0.2, "%.1f",
				std::floor(TimeElapsed * std::pow(10, 1)) / std::pow(10, 1));

			Text.SetColor(1.0, 1.0, 1.0);
			Text.Draw(rect.rx - 0.7 - cam.ShakeValueX,
				rect.ly + 0.25 - cam.ShakeValueY, 0.1, "HighScore: %d.%d", HighSec, HighMil);
		}
	}
}

void GameScore::SaveHighScoreToFile() {
	float RealTimeElpased = std::floor(TimeElapsed * std::pow(10, 1)) / std::pow(10, 1);
	int IntegerPart = static_cast<int>(TimeElapsed);
	int FloatPart = static_cast<int>(RealTimeElpased * 10) % 10;

	int PrevIntegerPart{};
	int PrevFloatPart{};

	switch (mp.MusicNumber) {
	case 1:  // easy
		PrevIntegerPart = dataUtil.LoadData("Easy Sec");
		PrevFloatPart = dataUtil.LoadData("Easy Mil");

		if (HighScore) {
			dataUtil.WriteData("Easy Sec", IntegerPart);
			dataUtil.WriteData("Easy Mil", FloatPart);
		}
		break;

	case 2: // normal
		PrevIntegerPart = dataUtil.LoadData("Normal Sec");
		PrevFloatPart = dataUtil.LoadData("Normal Sec");

		if (HighScore) {
			dataUtil.WriteData("Normal Sec", IntegerPart);
			dataUtil.WriteData("Normal Mil", FloatPart);
		}
		break;

	case 3: // hard
		PrevIntegerPart = dataUtil.LoadData("Hard Sec");
		PrevFloatPart = dataUtil.LoadData("Hard Mil");

		if (HighScore) {
			dataUtil.WriteData("Hard Sec", IntegerPart);
			dataUtil.WriteData("Hard Mil", FloatPart);
		}
		break;

	case 4: // harder
		PrevIntegerPart = dataUtil.LoadData("Harder Sec");
		PrevFloatPart = dataUtil.LoadData("Harder Mil");

		if (HighScore) {
			dataUtil.WriteData("Harder Sec", IntegerPart);
			dataUtil.WriteData("Harder Mil", FloatPart);
		}
		break;

	case 5: // insane
		PrevIntegerPart = dataUtil.LoadData("Insane Sec");
		PrevFloatPart = dataUtil.LoadData("Insane Mil");

		if (HighScore) {
			dataUtil.WriteData("Insane Sec", IntegerPart);
			dataUtil.WriteData("Insane Mil", FloatPart);
		}
		break;
	}
}

float GameScore::GetTime() {
	return TimeElapsed;
}