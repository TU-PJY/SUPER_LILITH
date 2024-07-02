#pragma once
#include <string>
#include <vector>

class MusicPlayer {
private:
	std::vector<unsigned int> PlayTime;

public:
	int MusicNumber = 1;
	float Threshold = 1.0;
	bool MusicPlayerInitState{};

	void SetToLobbyMode();
	void Init(std::string MusicName);
	void SetToPlayMode();
	void PlayMusic(int dir);
	void Update();
};
extern MusicPlayer mp;

