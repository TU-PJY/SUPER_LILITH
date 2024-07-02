#include "Cursor.h"
#include "MouseUtil.h"
#include "ImageUtil.h"
#include "CameraUtil.h"
#include <windows.h>

Cursor::Cursor() {
	Image = imageUtil.SetImage("cursor");
	SetColor(1.0, 1.0, 1.0);
	glutWarpPointer(GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 2);
}

void Cursor::Render() {
	InitTransform();
	Translate(DivideZoom(ASP(mouse.x) + 0.075, cam.Zoom), DivideZoom(mouse.y - 0.075, cam.Zoom));
	ScaleSpot(DivideZoom(0.15, cam.Zoom), DivideZoom(0.15, cam.Zoom));
	ProcessTransform();
	imageUtil.Draw(Image);
}

