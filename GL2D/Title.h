#pragma once
#include "ObjectBase.h"
#include "TextUtil.h"
#include <string>
#include <vector>

class Title : public OBJ_BASE {
private:
	TextUtil text, TitleText;
	int LobbyPage = 1;
	GLfloat TitlePosition{};

	std::vector<std::string> MusicInfo
	{
		"DJ Striden - Charisma VIP",
		"DJ Striden - Celestial Donimion",
		"DJ Striden - Sky Voyager",
		"DJ Striden - Cyber Bunked"
	};
	
public:
	Title();
	void InputSpecialKey(int KEY, bool KeyDown);
	void Update(float FT);
	void Render();
	void ChangeLobbyPage(int dir);
};

