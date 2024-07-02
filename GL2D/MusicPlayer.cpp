#include "MusicPlayer.h"
#include "SoundUtil.h"
#include "CameraUtil.h"
#include "FWM.h"

void MusicPlayer::SetToLobbyMode(){
	soundUtil.SetPlaySpeed("ch_bgm", 1.0);
}

void MusicPlayer::Init(std::string MusicName) {
	MusicNum = soundUtil.GetSoundNumif("stage");
	PlayTime.reserve(MusicNum);

	std::cout << MusicNum << std::endl;
	
	soundUtil.PlaySound(MusicName, "ch_bgm");
	soundUtil.SetPlaySpeed("ch_bgm", 0.0);
	soundUtil.SetBeatDetect("ch_bgm");

	MusicPlayerInitState = true;
}

int MusicPlayer::GetMusicNum() {
	return MusicNum;
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
		break;
	case 2:
		soundUtil.PlaySound("stage_normal", "ch_bgm", PlayTime[Page - 1]);
		break;
	case 3:
		soundUtil.PlaySound("stage_hard", "ch_bgm", PlayTime[Page - 1]);
		break;
	case 4:
		soundUtil.PlaySound("stage_harder", "ch_bgm", PlayTime[Page - 1]);
		break;
	case 5:
		soundUtil.PlaySound("stage_insane", "ch_bgm", PlayTime[Page - 1]);
		break;
	}

	soundUtil.SetBeatDetect("ch_bgm");

	MusicNumber = Page;
}

void MusicPlayer::Update() {
	if (MusicPlayerInitState) {
		if (fw.Mode() == "LobbyMode" || fw.Mode() == "ExitMode") {
			float BassValue = soundUtil.DetectBeat(0.0);
			camUtil.SetZoom(ZOOM::In, BassValue * 0.003);
		}

		else {
			float BassValue = soundUtil.DetectBeat(0.0);
			auto player = fw.Find("player");
			if (player) player->SetSize(BassValue * 0.02);
		}

		PlayTime[MusicNumber - 1] = soundUtil.GetPlayTime("ch_bgm");
	}
}
