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

	GLfloat BackObjectTimer{};

	bool StartAnimation{};

	std::vector<std::string> MusicInfo
	{
		"EASY",
		"NORMAL",
		"HARD",
		"HARDER",
		"INSANE"
	};

	std::vector<glm::vec3> ColorSet
	{
		{0.737255, 0.560784, 0.560784},
		{0.980392, 0.501961, 0.447059},
		{0.27451, 0.509804, 0.705882},
		{0.419608, 0.556863, 0.137255},
		{0, 0, 0}
	};

	std::vector<glm::vec3> ObjectColorSet
	{
		{1.0, 0.89, 0.89},
		{1.0, 0.949, 0.776},
		{0.549, 1.0, 1.0},
		{0.839, 1.0, 0.275},
		{1.0, 1.0, 1.0}
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
	void UpdateButtonState();
	int GetLobbyPage();
	void UpdateBackObject(float FT);
	glm::vec3 GetColorSet();
};

