#pragma once
#include "ObjectBase.h"
#include "TextUtil.h"

class Title : public OBJ_BASE {
private:
	unsigned int Image{};
	TextUtil text;
	int LobbyPage = 1;
	GLfloat TitlePosition{};

public:
	Title();
	void InputSpecialKey(int KEY, bool KeyDown);
	void Update(float FT);
	void Render();
	void ChangeLobbyPage(int dir);
};

