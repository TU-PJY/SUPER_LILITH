#pragma once
#include "ObjectBase.h"
#include "ImageUtil.h"
#include "FWM.h"
#include "MusicPlayer.h"
#include "Lobby.h"
#include <random>

enum class ObstacleType 
{Triangle, Square, Pentagon, Hexagon};

class Obstacle : public OBJ_BASE {
private:
	unsigned int Image{};
	int ShapeType{};
	GLfloat Size = 16;
	GLfloat Rotation{};
	GLfloat ShapeRotation{};
	GLfloat MoveSpeed = 1.6;

	bool IsSame{};
	bool B_ObstacleAdded{};
	bool FeedbackAdded{};
	GLfloat PlaySpeed = 1.0;
	GLfloat ShakeValue = 0.1;

	bool DirectionChanger{};
	bool IsMove{};

	std::random_device rd;

	std::vector<glm::vec3> ObjectColorSet
	{
		{1.0, 0.89, 0.89},
		{1.0, 0.949, 0.776},
		{0.549, 1.0, 1.0},
		{0.839, 1.0, 0.275},
		{1.0, 1.0, 1.0}
	};

	GLfloat MulValue{};

public:
	Obstacle(ObstacleType type, GLfloat R, GLfloat G, GLfloat B);
	void Stop();
	void ZeroMulValue();
	void Update(float FT);
	bool CheckShapeType();
	void Render();
	void SlowMusic(float FT);
	void ShakeCamera(float FT);
	void ProcessGameOver(float FT);
};


class BlinkingObstacle : public OBJ_BASE {
private:
	unsigned int Image{};
	float Frame{};
	GLfloat EndTimer{};

public:
	BlinkingObstacle() {
		Image = imageUtil.SetImage("feedback");

		SetColor(1.0, 0.0, 0.0);

		AlphaValue = 0.5;
		Scale(0.8, 0.8);
	}

	void Update(float FT) {
		InitTransform();
		Frame += FT * 10;

		if (Frame >= 30) {
			auto score = fw.Find("game_score");
			if (score) score->SaveHighScoreToFile();

			fw.SwitchMode(Lobby::LobbyMode, Lobby::SetController);
		}

		Scale(0.8, 0.8);
	}

	void Render() {
		ProcessTransform();

		if (Frame < 8) {
			if (int(Frame) % 2 == 0)
				imageUtil.Draw(Image);
		}
		else
			imageUtil.Draw(Image);
	}
};


class FeedBack : public OBJ_BASE {
private:
	unsigned int Image{};
	GLfloat Size{};

public:
	FeedBack(GLfloat R, GLfloat G, GLfloat B) {
		Image = imageUtil.SetImage("feedback");
		Size = 0.8;
		Scale(Size, Size);
		SetColor(R, G, B);
	}

	void Update(float FT) {
		InitTransform();

		Size = std::lerp(Size, 0.0, FT * 2);
		AlphaValue = std::lerp(AlphaValue, 0.0, FT * 3);

		Scale(Size, Size);

		if (Size <= 0.2)
			fw.DeleteSelf(this);
	}

	void Render() {
		ProcessTransform();
		imageUtil.Draw(Image);
	}
};



