#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "GLHeader.h"
#include <windows.h>

enum class Align
{ Default, Middle, Left };

class TextUtil {
private:
	glm::mat4 TranslateMatrix{ 1.0f }, RotateMatrix{ 1.0f }, ScaleMatrix{ 1.0f };
	GLfloat Rotation{};
	GLfloat AlphaValue{ 1.0f };
	glm::vec3 TextColor{ glm::vec3(1.0, 1.0, 1.0) };
	Align TextAlign{ Align::Default };

	unsigned int ModelLocation{}, TransparencyLocation{}, ObjectColorLocation{};

	HDC hDC{};
	GLuint FontBase{};
	GLYPHMETRICSFLOAT TextGlyph[96]{};

	GLfloat x{}, y{};

public:
	~TextUtil();
	void Init(const char* FontName, int type);
	void SetAlpha(GLfloat Value);
	void SetColor(GLfloat R, GLfloat G, GLfloat B);
	void SetAlign(Align AlignOpt);
	void Rotate(GLfloat Radians);
	void Draw(GLfloat X, GLfloat Y, GLfloat Size, const char* Format, ...);
	void GetLength(GLfloat& Length, unsigned Index, char* Text, GLfloat Size);
	void InitTransform();
	void ProcessTransform();
};