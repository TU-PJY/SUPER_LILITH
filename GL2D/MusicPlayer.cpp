#include "MusicPlayer.h"
#include "SoundUtil.h"
#include "CameraUtil.h"
#include "FWM.h"

void MusicPlayer::SetToLobbyMode(){
	soundUtil.SetFreqCutOff("ch_bgm", 200);
	soundUtil.SetPlaySpeed("ch_bgm", 1.0);
}

void MusicPlayer::Init(std::string MusicName) {
	PlayTime.reserve(10);

	soundUtil.PlaySound(MusicName, "ch_bgm");
	soundUtil.SetBeatDetect("ch_bgm");
	soundUtil.SetFreqCutOff("ch_bgm", 200);
}

void MusicPlayer::SetToPlayMode() {
	soundUtil.UnSetFreqCutOff("ch_bgm");
}

void MusicPlayer::PlayMusic(int Page){
	soundUtil.StopSound("ch_bgm");
	soundUtil.UnSetBeatDetect("ch_bgm");
	soundUtil.UnSetFreqCutOff("ch_bgm");

	switch (Page) {
	case 1:
		soundUtil.PlaySound("stage1", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	case 2:
		soundUtil.PlaySound("stage2", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	case 3:
		soundUtil.PlaySound("stage3", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	case 4:
		soundUtil.PlaySound("stage4", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 0.6;
		break;
	}

	soundUtil.SetBeatDetect("ch_bgm");
	soundUtil.SetFreqCutOff("ch_bgm", 200);

	MusicPage = Page;
}

void MusicPlayer::Update() {
	float BassValue = soundUtil.DetectBeat(Threshold);
	if(fw.Mode() == "LobbyMode")
		camUtil.SetZoom(ZOOM::In, BassValue * 0.003);
	else {
		auto player = fw.Find("player", SearchRange::One, Layer::L2);
		if (player) player->SetSize(BassValue * 0.01);
	}

	PlayTime[MusicPage - 1] = soundUtil.GetPlayTime("ch_bgm");
}
