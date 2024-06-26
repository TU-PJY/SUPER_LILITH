#include "GameScore.h"
#include "ImageUtil.h"
#include "DataUtil.h"
#include "CameraUtil.h"

GameScore::GameScore() {
	Text.Init(L"열정그자체", FW_NORMAL, TRUE);
	ScorePlate = imageUtil.SetImage("score_plate");

	Translate(rect.rx - 0.35, rect.ly + 0.14);
	ScaleSpot(0.3 * imageUtil.Aspect(350, 128), 0.3);
}

void GameScore::Update(float FT) {
	InitTransform();

	MiliSecond += FT;
	if (MiliSecond >= 1000)
		Second += 1;
	
	Translate(rect.rx - 0.35 - cam.ShakeValueX, rect.ly + 0.14 - cam.ShakeValueY);
	ScaleSpot(0.3 * imageUtil.Aspect(400, 128), 0.3);
}

void GameScore::Render() {
	ProcessTransform();
	imageUtil.Draw(ScorePlate);

	Text.Draw(rect.rx - 0.7 - cam.ShakeValueX, rect.ly + 0.07 - cam.ShakeValueY, 0.2, "%.1f",MiliSecond);
}

void GameScore::SaveHighScoreToFile() {

}

float GameScore::GetTime() {
	return MiliSecond;
}