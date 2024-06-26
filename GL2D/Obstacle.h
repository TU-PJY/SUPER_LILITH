#pragma once
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "FWM.h"
#include "MusicPlayer.h"
#include "Lobby.h"

enum class ObstacleType 
{Triangle, Square, Pentagon, Hexagon};

class Obstacle : public OBJ_BASE {
private:
	unsigned int Image{};
	int ShapeType{};
	GLfloat Size = 16;
	GLfloat Rotation{};
	GLfloat MoveSpeed = 1.5;

	bool IsSame{};
	bool B_ObstacleAdded{};
	bool FeedbackAdded{};
	GLfloat PlaySpeed = 1.0;
	GLfloat ShakeValue = 0.1;

public:
	Obstacle(ObstacleType type, GLfloat R, GLfloat G, GLfloat B);
	void SetMoveSpeed(GLfloat Speed);
	void Update(float FT);
	bool CheckShapeType();
	void Render();
	void SlowMusic(float FT);
	void ShakeCamera(float FT);
	void ProcessGameOver(float FT);
};

#include <iostream>
class BlinkingObstacle : public OBJ_BASE {
private:
	int ShapeType{};
	unsigned int Image{};
	float Frame{};
	glm::vec3 ColorSet{};
	GLfloat ShapeSize{};

	GLfloat EndTimer{};

public:
	BlinkingObstacle(int Type, GLfloat R, GLfloat G, GLfloat B, GLfloat Rotation, GLfloat Size) {
		switch (Type) {
		case 0:
			Image = imageUtil.SetImage("obstacle_triangle");
			break;

		case 1:
			Image = imageUtil.SetImage("obstacle_square");
			break;

		case 2:
			Image = imageUtil.SetImage("obstacle_pentagon");
			break;

		case 3:
			Image = imageUtil.SetImage("obstacle_hexagon");
			break;

		}

		SetColor(R, G, B);

		ColorSet.r = R;
		ColorSet.g = G;
		ColorSet.b = B;

		auto player = fw.Find("player", SearchRange::One, Layer::L2);
		if (player) Rotate(player->GetRotation() + 30);

		ShapeSize = Size;
		Scale(ShapeSize, ShapeSize);
	}

	void Update(float FT) {
		InitTransform();

		Frame += FT * 10;

		if (Frame < 8) {
			if (int(Frame) % 2 == 0)
				SetColor(1.0, 0.0, 0.0);
			else
				SetColor(ColorSet.r, ColorSet.g, ColorSet.b);
		}

		else {
			SetColor(1.0, 0.0, 0.0);
			EndTimer += FT * 10;
			if (EndTimer >= 15) {
				mp.SetToLobbyMode();
				fw.SwitchMode(Lobby::LobbyMode, Lobby::SetController);
			}
		}

		Scale(ShapeSize, ShapeSize);

		auto player = fw.Find("player", SearchRange::One, Layer::L2);
		if (player) Rotate(player->GetRotation() + 30);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};


class FeedBack : public OBJ_BASE {
private:
	unsigned int Image{};
	GLfloat Size{};

public:
	FeedBack() {
		Image = imageUtil.SetImage("feedback");
		Size = 0.8;
		Scale(Size, Size);
		SetColor(0.0, 1.0, 0.0);
	}

	void Update(float FT) {
		InitTransform();

		Size = std::lerp(Size, 0.0, FT * 2);
		AlphaValue = std::lerp(AlphaValue, 0.0, FT * 2);

		Scale(Size, Size);

		if (Size <= 0.2)
			fw.DeleteSelf(this);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};



