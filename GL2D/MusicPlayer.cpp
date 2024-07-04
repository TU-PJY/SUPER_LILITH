#include "MusicPlayer.h"
#include "SoundUtil.h"
#include "CameraUtil.h"
#include "DataUtil.h"
#include "FWM.h"
#include "Bar.h"

void MusicPlayer::SetToLobbyMode(){
	soundUtil.SetPlaySpeed("ch_bgm", 1.0);
}

void MusicPlayer::Init(std::string MusicName) {
	EffectDisable = dataUtil.LoadData("Disable Effect");
	MusicReset = dataUtil.LoadData("Music Reset");

	MusicNum = soundUtil.GetSoundNumif("stage");
	PlayTime.reserve(MusicNum);
	
	soundUtil.PlaySound(MusicName, "ch_bgm");
	soundUtil.SetPlaySpeed("ch_bgm", 0.0);
	soundUtil.SetBeatDetect("ch_bgm");

	MusicPlayerInitState = true;
}

void MusicPlayer::ChangeEffectSetting() {
	ClearMessageBar();
	if (!EffectDisable) {
		fw.AddObject(new Bar(3), "alert_effect_off", Layer::L3);
		EffectDisable = true;
	}
	else {
		fw.AddObject(new Bar(4), "alert_effect_on", Layer::L3);
		EffectDisable = false;
	}

	dataUtil.WriteData("Disable Effect", EffectDisable);
}

void MusicPlayer::ChangeMusicSetting() {
	ClearMessageBar();
	if (!MusicReset) {
		fw.AddObject(new Bar(1), "alert_music_reset", Layer::L3);
		for (auto& T : PlayTime)
			T = 0;

		MusicReset = true;
	}
	else {
		fw.AddObject(new Bar(2), "alert_music_resume", Layer::L3);
		MusicReset = false;
	}

	dataUtil.WriteData("Music Reset", MusicReset);
}

void MusicPlayer::ClearMessageBar() {
	fw.DeleteObject("alert_music_reset", DeleteRange::All);
	fw.DeleteObject("alert_music_resume", DeleteRange::All);
	fw.DeleteObject("alert_effect_off", DeleteRange::All);
	fw.DeleteObject("alert_effect_on", DeleteRange::All);
}

int MusicPlayer::GetMusicNum() {
	return MusicNum;
}

void MusicPlayer::SetToPlayMode() {
	soundUtil.UnSetFreqCutOff("ch_bgm");

	if (MusicReset)
		soundUtil.ReplaySound("ch_bgm");
}

void MusicPlayer::PlayMusic(int Page){
	soundUtil.StopSound("ch_bgm");
	soundUtil.UnSetBeatDetect("ch_bgm");
	soundUtil.UnSetFreqCutOff("ch_bgm");

	if (!MusicReset) {
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
	}

	else {
		switch (Page) {
		case 1:
			soundUtil.PlaySound("stage_easy", "ch_bgm");
			break;
		case 2:
			soundUtil.PlaySound("stage_normal", "ch_bgm");
			break;
		case 3:
			soundUtil.PlaySound("stage_hard", "ch_bgm");
			break;
		case 4:
			soundUtil.PlaySound("stage_harder", "ch_bgm");
			break;
		case 5:
			soundUtil.PlaySound("stage_insane", "ch_bgm");
			break;
		}
	}

	soundUtil.SetBeatDetect("ch_bgm");

	MusicNumber = Page;
}

void MusicPlayer::Update() {
	if (MusicPlayerInitState) {
		if (!EffectDisable) {
			if (fw.Mode() != "PlayMode" && fw.Mode() != "PauseMode") {
				float BassValue = soundUtil.DetectBeat(0.0);
				camUtil.SetZoom(ZOOM::In, BassValue * 0.003);

				for (int i = 0; i < fw.Size(Layer::L1); ++i) {
					auto object = fw.Find("back_object", Layer::L1, i);
					if (object) object->SetSize(BassValue * 0.01);
				}
			}

			else if(fw.Mode() == "PlayMode") {
				float BassValue = soundUtil.DetectBeat(0.0);
				auto player = fw.Find("player");
				if (player) {
					switch (MusicNumber) {
					case 1:
						player->SetSize(BassValue * 0.02);
						break;
					case 2:
						player->SetSize(BassValue * 0.02);
						break;
					case 3:
						player->SetSize(BassValue * 0.02);
						break;
					case 4:
						player->SetSize(BassValue * 0.02);
						break;
					case 5:
						player->SetSize(BassValue * 0.02);
						break;
					}
				}
			}
		}

		if(!MusicReset)
			PlayTime[MusicNumber - 1] = soundUtil.GetPlayTime("ch_bgm");
	}
}
