#include "RenderModeUtil.h"
#include "CameraUtil.h"

void RenderModeUtil::SetTextMode() {
	glUseProgram(TextShader);
	cam.SetCamera();
	cam.ProcessTransform(true);
}

void RenderModeUtil::SetImageMode() {
	glUseProgram(ImageShader);
	cam.SetCamera();
	cam.ProcessTransform(false);
}