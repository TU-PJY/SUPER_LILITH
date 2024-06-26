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
	GLfloat ShapeRotation{};
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


class BlinkingObstacle : public OBJ_BASE {
private:
	int ShapeType{};
	unsigned int Image{};
	float Frame{};
	glm::vec3 ColorSet{};
	GLfloat ShapeSize{};

	GLfloat EndTimer{};

public:
	BlinkingObstacle() {
		Image = imageUtil.SetImage("feedback");

		SetColor(1.0, 0.0, 0.0);

		ShapeSize = 0.8;
		Scale(ShapeSize, ShapeSize);
		AlphaValue = 0.7;
	}

	void Update(float FT) {
		InitTransform();

		Frame += FT * 10;

		Scale(ShapeSize, ShapeSize);

		if (Frame >= 30) {
			mp.SetToLobbyMode();
			fw.SwitchMode(Lobby::LobbyMode, Lobby::SetController);
		}
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



