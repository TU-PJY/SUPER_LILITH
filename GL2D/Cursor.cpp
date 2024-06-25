#include "Cursor.h"
#include "MouseUtil.h"
#include "ImageUtil.h"
#include "CameraUtil.h"

Cursor::Cursor() {
	Image = imageUtil.SetImage("cursor");
	SetColor(1.0, 1.0, 1.0);
}

void Cursor::Render() {
	InitTransform();
	Translate(DivideZoom(ASP(mouse.x) + 0.075, cam.Zoom), DivideZoom(mouse.y - 0.075, cam.Zoom));
	ScaleSpot(DivideZoom(0.15, cam.Zoom), DivideZoom(0.15, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(Image);
}

