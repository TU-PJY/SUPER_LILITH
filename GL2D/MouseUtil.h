#pragma once
#include "GLHeader.h"

class MouseUtil {
public:
	GLfloat x{}, y{};
	void ConvertPosition(int X, int Y);
};
extern MouseUtil mouse;