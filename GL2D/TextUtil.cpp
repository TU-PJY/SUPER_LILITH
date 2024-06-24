#include "TextUtil.h"
#include "RenderModeUtil.h"

TextUtilUnicode::~TextUtilUnicode() {
	glDeleteLists(FontBase, 65536);
	DeleteDC(hDC);
}

void TextUtilUnicode::Init(const wchar_t* FontName, int type) {
	hDC = wglGetCurrentDC();

	HFONT Font;
	HFONT OldFont;

	FontBase = glGenLists(65536);

	Font = CreateFont(
		-1, 0, 0, 0, type, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE | VARIABLE_PITCH, FontName
	);

	OldFont = (HFONT)SelectObject(hDC, Font);
	wglUseFontOutlinesW(hDC, 0, 65536, FontBase, 0.0f, 0.0f, WGL_FONT_POLYGONS, TextGlyph);

	SelectObject(hDC, OldFont);
	DeleteObject(Font);
}

void TextUtilUnicode::SetAlpha(GLfloat Value) {
	AlphaValue = Value;
}

void TextUtilUnicode::SetColor(GLfloat R, GLfloat G, GLfloat B) {
	TextColor.r = R;
	TextColor.g = G;
	TextColor.b = B;
}

void TextUtilUnicode::SetAlign(Align AlignOpt) {
	TextAlign = AlignOpt;
}

void TextUtilUnicode::Rotate(GLfloat Radians) {
	Rotation = Radians;
}

void TextUtilUnicode::Draw(GLfloat X, GLfloat Y, GLfloat Size, const wchar_t* Format, ...) {
	wchar_t Text[256];

	va_list Args{};

	va_start(Args, Format);
	vswprintf(Text, sizeof(Text)/ sizeof(wchar_t), Format, Args);
	va_end(Args);

	unsigned char CharIndex{};
	GLfloat CurrentPositionX = 0.0f;
	GLfloat Length{};

	if (TextAlign != Align::Default)
		GetLength(Length, CharIndex, Text, Size);

	for (int i = 0; i < wcslen(Text); ++i) {
		InitTransform();
		RotateMatrix = rotate(RotateMatrix, glm::radians(Rotation), glm::vec3(0.0, 0.0, 1.0));
		ScaleMatrix = scale(ScaleMatrix, glm::vec3(Size, Size, 0.0));

		switch (TextAlign) {
		case Align::Default:
			TranslateMatrix = translate(TranslateMatrix, glm::vec3(X + CurrentPositionX, Y, 0.0));
			break;

		case Align::Middle:
			TranslateMatrix = translate(TranslateMatrix, glm::vec3(X - Length / 2 + CurrentPositionX, Y, 0.0));
			break;

		case Align::Left:
			TranslateMatrix = translate(TranslateMatrix, glm::vec3(X - Length + CurrentPositionX, Y, 0.0));
			break;
		}

		ProcessTransform();

		if (Format == NULL)
			return;

		glPushAttrib(GL_LIST_BIT);
		glListBase(FontBase);
		glCallLists(1, GL_UNSIGNED_SHORT, &Text[i]);
		glPopAttrib();

		unsigned int CharIndex = Text[i];
		if (CharIndex < 65536)
			CurrentPositionX += TextGlyph[CharIndex].gmfCellIncX * (Size / 1.0f);
	}
}

void TextUtilUnicode::GetLength(GLfloat& Length, unsigned Index, const wchar_t* Text, GLfloat Size) {
	Length = 0.0f;
	for (int i = 0; i < wcslen(Text); ++i) {
		unsigned int CharIndex = Text[i];
		if (CharIndex < 65536)
			Length += TextGlyph[CharIndex].gmfCellIncX * (Size / 1.0f);
	}
}

void TextUtilUnicode::InitTransform() {
	TranslateMatrix = glm::mat4(1.0f);
	RotateMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::mat4(1.0f);
}

void TextUtilUnicode::ProcessTransform() {
	renderMode.SetTextMode();

	TransparencyLocation = glGetUniformLocation(TextShader, "transparency");
	glUniform1f(TransparencyLocation, AlphaValue);

	ModelLocation = glGetUniformLocation(TextShader, "model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, value_ptr(RotateMatrix * TranslateMatrix * ScaleMatrix));

	ObjectColorLocation = glGetUniformLocation(TextShader, "objectColor");
	glUniform3f(ObjectColorLocation, TextColor.r, TextColor.g, TextColor.b);

	ModelLocation = glGetUniformLocation(TextShader, "model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, value_ptr(RotateMatrix * TranslateMatrix * ScaleMatrix));
}



TextUtil::~TextUtil() {
	glDeleteLists(FontBase, 96);
	DeleteDC(hDC);
}

void TextUtil::Init(const wchar_t* FontName, int type) {
	hDC = wglGetCurrentDC();

	HFONT Font;
	HFONT OldFont;

	FontBase = glGenLists(96);

	Font = CreateFont(
		-1, 0, 0, 0, type, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE | VARIABLE_PITCH, FontName
	);

	OldFont = (HFONT)SelectObject(hDC, Font);
	wglUseFontOutlines(hDC, 32, 96, FontBase, 0.0f, 0.0f, WGL_FONT_POLYGONS, TextGlyph);

	SelectObject(hDC, OldFont);
	DeleteObject(Font);
}

void TextUtil::SetAlpha(GLfloat Value) {
	AlphaValue = Value;
}

void TextUtil::SetColor(GLfloat R, GLfloat G, GLfloat B) {
	TextColor.r = R;
	TextColor.g = G;
	TextColor.b = B;
}

void TextUtil::SetAlign(Align AlignOpt) {
	TextAlign = AlignOpt;
}

void TextUtil::Rotate(GLfloat Radians) {
	Rotation = Radians;
}

void TextUtil::Draw(GLfloat X, GLfloat Y, GLfloat Size, const char* Format, ...) {
	char Text[256];

	va_list Args{};

	va_start(Args, Format);
	vsprintf(Text, Format, Args);
	va_end(Args);

	unsigned char CharIndex{};
	GLfloat CurrentPositionX = 0.0f;
	GLfloat Length{};

	if (TextAlign != Align::Default)
		GetLength(Length, CharIndex, Text, Size);

	for (int i = 0; i < strlen(Text); ++i) {
		InitTransform();
		RotateMatrix = rotate(RotateMatrix, glm::radians(Rotation), glm::vec3(0.0, 0.0, 1.0));
		ScaleMatrix = scale(ScaleMatrix, glm::vec3(Size, Size, 0.0));

		switch (TextAlign) {
		case Align::Default:
			TranslateMatrix = translate(TranslateMatrix, glm::vec3(X + CurrentPositionX, Y, 0.0));
			break;

		case Align::Middle:
			TranslateMatrix = translate(TranslateMatrix, glm::vec3(X - Length / 2 + CurrentPositionX, Y, 0.0));
			break;

		case Align::Left:
			TranslateMatrix = translate(TranslateMatrix, glm::vec3(X - Length + CurrentPositionX, Y, 0.0));
			break;
		}

		ProcessTransform();

		if (Format == NULL)
			return;

		glPushAttrib(GL_LIST_BIT);
		glListBase(FontBase - 32);
		glCallLists(1, GL_UNSIGNED_BYTE, &Text[i]);
		glPopAttrib();

		CharIndex = Text[i] - 32;
		if (CharIndex < sizeof(TextGlyph) / sizeof(TextGlyph[i]))
			CurrentPositionX += TextGlyph[CharIndex].gmfCellIncX * (Size / 1.0);
	}
}

void TextUtil::GetLength(GLfloat& Length, unsigned Index, const char* Text, GLfloat Size) {
	Length = 0.0f;
	for (int i = 0; i < strlen(Text); ++i) {
		Index = Text[i] - 32;
		if (Index < sizeof(TextGlyph) / sizeof(TextGlyph[i]))
			Length += TextGlyph[Index].gmfCellIncX * (Size / 1.0);
	}
}

void TextUtil::InitTransform() {
	TranslateMatrix = glm::mat4(1.0f);
	RotateMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::mat4(1.0f);
}

void TextUtil::ProcessTransform() {
	renderMode.SetTextMode();

	TransparencyLocation = glGetUniformLocation(TextShader, "transparency");
	glUniform1f(TransparencyLocation, AlphaValue);

	ModelLocation = glGetUniformLocation(TextShader, "model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, value_ptr(RotateMatrix * TranslateMatrix * ScaleMatrix));

	ObjectColorLocation = glGetUniformLocation(TextShader, "objectColor");
	glUniform3f(ObjectColorLocation, TextColor.r, TextColor.g, TextColor.b);

	ModelLocation = glGetUniformLocation(TextShader, "model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, value_ptr(RotateMatrix * TranslateMatrix * ScaleMatrix));
}