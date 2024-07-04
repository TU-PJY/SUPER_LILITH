#pragma once
#include <string>
#include <vector>

class MusicPlayer {
private:
	std::vector<unsigned int> PlayTime;

public:
	int MusicNumber = 1;
	int MusicNum{};
	float Threshold = 1.0;
	bool MusicPlayerInitState{};

	bool MusicReset{};
	bool EffectDisable{};

	void SetToLobbyMode();
	void Init(std::string MusicName);
	void ChangeEffectSetting();
	void ChangeMusicSetting();
	void ClearMessageBar();
	int GetMusicNum();
	void SetToPlayMode();
	void PlayMusic(int dir);
	void Update();
};
extern MusicPlayer mp;

