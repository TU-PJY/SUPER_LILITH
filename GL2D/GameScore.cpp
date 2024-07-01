#include "GameScore.h"
#include "ImageUtil.h"
#include "DataUtil.h"
#include "CameraUtil.h"
#include "MusicPlayer.h"

GameScore::GameScore() {
	Text.Init(L"열정그자체", FW_NORMAL, TRUE);
	ScorePlate = imageUtil.SetImage("score_plate");

	Translate(rect.rx - 0.35, rect.ly + 0.14);
	ScaleSpot(0.3 * imageUtil.Aspect(350, 128), 0.3);

	// 선택한 난이도에 따라 시작 난이도가 달라진다
	int DiffValue = mp.MusicNumber - 1;

	switch (DiffValue) {
	case 0:  // easy
		Diff = 0;
		break;
	case 1:  // normal
		Diff = 20;
		break;
	case 2:  // hard
		Diff = 60;
		break;
	case 3:  // harder
		Diff = 100;
		break;
	case 4:  // insane
		Diff = 140;
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
	InitTransform();

	if (!StopState) {
		TimeElapsed += FT;
		Diff += FT;
	}
	
	Translate(rect.rx - 0.35 - cam.ShakeValueX, rect.ly + 0.14 - cam.ShakeValueY);
	ScaleSpot(0.3 * imageUtil.Aspect(400, 128), 0.3);
}

void GameScore::Render() {
	ProcessTransform();
	imageUtil.Draw(ScorePlate);

	Text.Draw(rect.rx - 0.7 - cam.ShakeValueX, rect.ly + 0.07 - cam.ShakeValueY, 0.2, "%.1f",TimeElapsed);
}

void GameScore::SaveHighScoreToFile() {

}

float GameScore::GetTime() {
	return TimeElapsed;
}