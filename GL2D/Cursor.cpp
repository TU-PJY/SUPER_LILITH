#include "Cursor.h"
#include "MouseUtil.h"
#include "ImageUtil.h"

Cursor::Cursor() {
	Image = imageUtil.SetImage("cursor");
	SetColor(1.0, 1.0, 1.0);
}

void Cursor::Render() {
	InitTransform();
	Translate(ASP(mouse.x) + 0.075, mouse.y - 0.075);
	ScaleSpot(0.15, 0.15);
	ProcessTransform();
	imageUtil.Draw(Image);
}

