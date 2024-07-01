#include "MusicPlayer.h"
#include "SoundUtil.h"
#include "CameraUtil.h"
#include "FWM.h"

void MusicPlayer::SetToLobbyMode(){
	soundUtil.SetPlaySpeed("ch_bgm", 1.0);
}

void MusicPlayer::Init(std::string MusicName) {
	PlayTime.reserve(10);

	soundUtil.PlaySound(MusicName, "ch_bgm");
	soundUtil.SetPlaySpeed("ch_bgm", 0.0);
	soundUtil.SetBeatDetect("ch_bgm");
	Threshold = 1.0;
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
		soundUtil.PlaySound("stage_easy", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	case 2:
		soundUtil.PlaySound("stage_normal", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	case 3:
		soundUtil.PlaySound("stage_hard", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	case 4:
		soundUtil.PlaySound("stage_harder", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	case 5:
		soundUtil.PlaySound("stage_insane", "ch_bgm", PlayTime[Page - 1]);
		Threshold = 1.0;
		break;
	}

	soundUtil.SetBeatDetect("ch_bgm");

	MusicNumber = Page;
}

void MusicPlayer::Update() {
	if (fw.Mode() == "LobbyMode") {
		float BassValue = soundUtil.DetectBeat(0.0);
		camUtil.SetZoom(ZOOM::In, BassValue * 0.003);
	}

	else {
		float BassValue = soundUtil.DetectBeat(0.0);
		auto player = fw.Find("player");
		if (player) player->SetSize(BassValue * 0.01);
	}

	PlayTime[MusicNumber - 1] = soundUtil.GetPlayTime("ch_bgm");
}
