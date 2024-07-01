#pragma once
#include "ObjectBase.h"
#include "TextUtil.h"
#include <string>
#include <vector>

class Title : public OBJ_BASE {
private:
	int LobbyPage = 1;
	int BgmNum{};

	TextUtil Text;
	GLfloat TitlePosition{};
	GLfloat TitleMovePosition = 0.8;
	GLfloat PlaySpeed = 0.0;

	bool StartAnimation{};

	std::vector<std::string> MusicInfo
	{
		"DJ Striden - Dare",
		"DJ Striden - Retropolis",
		"DJ Striden - Starlight Shifter",
		"DJ Striden - Singularity",
		"DJ Striden - Sentient"
	};
	
public:
	Title(int Page);
	void InputSpecialKey(int KEY, bool KeyDown);
	void InputKey(unsigned char KEY, bool KeyDown);
	bool GetAnimationtate();
	void EnableStartAnimation();
	void Update(float FT);
	void Render();
	void ChangeLobbyPage(int dir);
	int GetLobbyPage();
};

