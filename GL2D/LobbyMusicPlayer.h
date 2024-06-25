#pragma once
#include "ObjectBase.h"
#include <string>
#include <vector>

class LobbyMusicPlayer : public OBJ_BASE {
private:
	int MusicPage = 1;
	float Threshold{};

	std::vector<int> PlayTime;

public:
	LobbyMusicPlayer(std::string MusicName);
	void PlayMusic(int dir);
	void Update(float FT);
};

