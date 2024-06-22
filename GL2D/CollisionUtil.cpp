#include "CollisionUtil.h"
#include "RenderModeUtil.h"
#include "ImageUtil.h"
#include "CameraUtil.h"


void AABB::Init() {
	if (ShowBoundBox) {
		Box = imageUtil.SetImage("gl2d_boundbox");
		text.Init("arial", FW_NORMAL);
		text.SetColor(1.0, 0.0, 0.0);
	}
}

void AABB::Update(GLfloat X, GLfloat Y, GLfloat xScale, GLfloat yScale, bool UseViewportPosition) {
	LeftX = X - xScale / 2;
	RightX = X + xScale / 2;
	LeftY = Y - yScale / 2;
	RightY = Y + yScale / 2;

	if (ShowBoundBox) {
		InitTransform();

		ScaleMatrix = scale(ScaleMatrix, glm::vec3(xScale, yScale, 0.0));
		TranslateMatrix = translate(TranslateMatrix, glm::vec3(X, Y, 0.0));

		ProcessTransform();
		imageUtil.Draw(Box);

		if (UseViewportPosition) {
			text.SetAlign(Align::Left);
			text.Draw(LeftX - DivideZoom(0.02, cam.Zoom), LeftY, DivideZoom(0.07, cam.Zoom), "[%.2f, %.2f]", DivideASP(X) - xScale / 2, LeftY);
			text.SetAlign(Align::Default);
			text.Draw(RightX + DivideZoom(0.02, cam.Zoom), RightY, DivideZoom(0.07, cam.Zoom), "[%.2f, %.2f]", DivideASP(X) + xScale / 2, RightY);
			text.SetAlign(Align::Middle);
			text.Draw(X, Y, DivideZoom(0.07, cam.Zoom), "[%.2f, %.2f]", DivideASP(X), Y);
		}

		else {
			text.SetAlign(Align::Left);
			text.Draw(LeftX - DivideZoom(0.02, cam.Zoom), LeftY, DivideZoom(0.07, cam.Zoom), "[%.2f, %.2f]", X - xScale / 2, LeftY);
			text.SetAlign(Align::Default);
			text.Draw(RightX + DivideZoom(0.02, cam.Zoom), RightY, DivideZoom(0.07, cam.Zoom), "[%.2f, %.2f]", X + xScale / 2, RightY);
			text.SetAlign(Align::Middle);
			text.Draw(X, Y, DivideZoom(0.07, cam.Zoom), "[%.2f, %.2f]", X, Y);
		}
	}
}

bool AABB::CheckCollisionAABB(AABB aabb) {
	if (RightX < aabb.LeftX || LeftX > aabb.RightX)
		return false;

	if (RightY < aabb.LeftY || LeftY > aabb.RightY)
		return false;

	return true;
}

bool AABB::CheckCollisionDot(GLfloat X, GLfloat Y) {
	if ((LeftX <= X && X <= RightX) && (LeftY <= Y && Y <= RightY))
		return true;

	return false;
}

void AABB::InitTransform() {
	TranslateMatrix = glm::mat4(1.0f);
	RotateMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::mat4(1.0f);
}

void AABB::ProcessTransform() {
	renderMode.SetImageMode();

	TransparencyLocation = glGetUniformLocation(ImageShader, "transparency");
	glUniform1f(TransparencyLocation, 1.0);

	ObjectColorLocation = glGetUniformLocation(TextShader, "objectColor");
	glUniform3f(ObjectColorLocation, 1.0, 0.0, 0.0);

	ModelLocation = glGetUniformLocation(ImageShader, "model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, value_ptr(RotateMatrix * TranslateMatrix * ScaleMatrix));
}