#include "MouseUtil.h"

void MouseUtil::ConvertPosition(int X, int Y) {
	x = (GLfloat)(X - (GLfloat)WIDTH / 2.0) * (GLfloat)(1.0 / (GLfloat)(WIDTH / 2.0));
	y = -(GLfloat)(Y - (GLfloat)HEIGHT / 2.0) * (GLfloat)(1.0 / (GLfloat)(HEIGHT / 2.0));
}