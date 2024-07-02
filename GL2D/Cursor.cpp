#include "Cursor.h"
#include "MouseUtil.h"
#include "ImageUtil.h"
#include "CameraUtil.h"
#include "FWM.h"
#include <windows.h>

Cursor::Cursor() {
	Image = imageUtil.SetImage("cursor");
	SetColor(1.0, 1.0, 1.0);
	glutWarpPointer(GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXSCREEN) / 4, GetSystemMetrics(SM_CYSCREEN) / 2);
}

void Cursor::Update(float FT) {
	InitTransform();
	Translate(DivideZoom(ASP(mouse.x) + 0.075, cam.Zoom), DivideZoom(mouse.y - 0.075, cam.Zoom));
	ScaleSpot(DivideZoom(0.15, cam.Zoom), DivideZoom(0.15, cam.Zoom));
}

void Cursor::Render() {
	ProcessTransform();
	imageUtil.Draw(Image);
}
