#pragma once
#include <string>
#include <vector>

class MusicPlayer {
private:
	float Threshold{};

	std::vector<int> PlayTime;

public:
	int MusicPage = 1;
	float Threashol = 1.0;

	void SetToLobbyMode();
	void Init(std::string MusicName);
	void SetToPlayMode();
	void PlayMusic(int dir);
	void Update();
};
extern MusicPlayer mp;

