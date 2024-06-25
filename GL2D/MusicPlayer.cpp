#include "MusicPlayer.h"
#include "SoundUtil.h"
#include "CameraUtil.h"

void MusicPlayer::SetToLobbyMode(std::string MusicName){
	PlayTime.reserve(10);

	soundUtil.PlaySound(MusicName, "ch_bgm");
	soundUtil.SetBeatDetect("ch_bgm");
	soundUtil.SetFreqCutOff("ch_bgm", 200);
}

void MusicPlayer::PlayMusic(int Page){
	soundUtil.StopSound("ch_bgm");
	soundUtil.UnSetBeatDetect("ch_bgm");
	soundUtil.UnSetFreqCutOff("ch_bgm");

	switch (Page) {
	case 1:
		soundUtil.PlaySound("stage1", "ch_bgm", PlayTime[Page - 1]);
		break;
	case 2:
		soundUtil.PlaySound("stage2", "ch_bgm", PlayTime[Page - 1]);
		break;
	case 3:
		soundUtil.PlaySound("stage3", "ch_bgm", PlayTime[Page - 1]);
		break;
	case 4:
		soundUtil.PlaySound("stage4", "ch_bgm", PlayTime[Page - 1]);
		break;
	}

	soundUtil.SetBeatDetect("ch_bgm");
	soundUtil.SetFreqCutOff("ch_bgm", 200);

	MusicPage = Page;
}

void MusicPlayer::Update() {
	float BassValue = soundUtil.DetectBeat(0.0);
	camUtil.SetZoom(ZOOM::In, BassValue * 0.002);

	PlayTime[MusicPage - 1] = soundUtil.GetPlayTime("ch_bgm");
}
