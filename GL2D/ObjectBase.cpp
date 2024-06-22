#include "ObjectBase.h"
#include "RenderModeUtil.h"


void OBJ_BASE::Translate(GLfloat X, GLfloat Y) {
	TranslateMatrix = translate(TranslateMatrix, glm::vec3(X, Y, 0.0));
}

void OBJ_BASE::Rotate(GLfloat Radians) {
	RotateMatrix = rotate(RotateMatrix, glm::radians(Radians), glm::vec3(0.0, 0.0, 1.0));
}

void OBJ_BASE::Scale(GLfloat X, GLfloat Y) {
	ScaleMatrix = scale(ScaleMatrix, glm::vec3(X, Y, 0.0));
}

void OBJ_BASE::RotateSpot(GLfloat Radians) {
	TranslateMatrix = rotate(TranslateMatrix, glm::radians(Radians), glm::vec3(0.0, 0.0, 1.0));
}

void OBJ_BASE::RotateAxis(GLfloat Radians, GLfloat AxisX, GLfloat AxisY) {
	TranslateMatrix = translate(TranslateMatrix, glm::vec3(AxisX, AxisY, 0.0));
	TranslateMatrix = rotate(TranslateMatrix, glm::radians(Radians), glm::vec3(0.0, 0.0, 1.0));
	TranslateMatrix = translate(TranslateMatrix, glm::vec3(-AxisX, -AxisY, 0.0));
}

void OBJ_BASE::SetColor(GLfloat R, GLfloat G, GLfloat B) {
	ObjectColor.r = R;
	ObjectColor.g = G;
	ObjectColor.b = B;
}

void OBJ_BASE::SetAlpha(GLfloat Value) {
	AlphaValue = Value;
}

void OBJ_BASE::InitTransform() {
	TranslateMatrix = glm::mat4(1.0f);
	RotateMatrix = glm::mat4(1.0f);
	ScaleMatrix = glm::mat4(1.0f);
}

void OBJ_BASE::ProcessTransform() {
	renderMode.SetImageMode();

	TransparencyLocation = glGetUniformLocation(ImageShader, "transparency");
	glUniform1f(TransparencyLocation, AlphaValue);

	ObjectColorLocation = glGetUniformLocation(TextShader, "objectColor");
	glUniform3f(ObjectColorLocation, ObjectColor.r, ObjectColor.g, ObjectColor.b);

	ModelLocation = glGetUniformLocation(ImageShader, "model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, value_ptr(RotateMatrix * TranslateMatrix * ScaleMatrix));
}