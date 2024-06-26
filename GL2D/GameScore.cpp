#include "GameScore.h"
#include "ImageUtil.h"
#include "DataUtil.h"
#include "CameraUtil.h"

GameScore::GameScore() {
	Text.Init(L"열정 그 자체", FW_NORMAL, TRUE);
	ScorePlate = imageUtil.SetImage("score_plate");

	Translate(rect.rx - 0.35, rect.ly + 0.14);
	ScaleSpot(0.3 * imageUtil.Aspect(350, 128), 0.3);
}

void GameScore::Update(float FT) {
	InitTransform();
	
	Translate(rect.rx - 0.35 - cam.ShakeValueX, rect.ly + 0.14 - cam.ShakeValueY);
	ScaleSpot(0.3 * imageUtil.Aspect(400, 128), 0.3);
}

void GameScore::Render() {
	ProcessTransform();
	imageUtil.Draw(ScorePlate);
}

void GameScore::SaveHighScoreToFile() {

}