#pragma once
#include <string>
#include <vector>

class MusicPlayer {
private:
	int MusicPage = 1;
	float Threshold{};

	std::vector<int> PlayTime;

public:
	void SetToLobbyMode(std::string MusicName);
	void PlayMusic(int dir);
	void Update();
};
extern MusicPlayer mp;

