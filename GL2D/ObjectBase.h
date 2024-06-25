#pragma once
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <string>

class OBJ_BASE {
public:
	bool ObjectDeleteDescriptor{};
	bool FloatingSpecifiedDescriptor{};
	std::string ObjectTag{};

	glm::mat4 TranslateMatrix{ 1.0f }, RotateMatrix{ 1.0f }, ScaleMatrix{ 1.0f };
	glm::vec3 ObjectColor{ glm::vec3(0.0, 0.0, 0.0) };
	GLfloat AlphaValue{ 1.0f };

	unsigned int ModelLocation{}, TransparencyLocation{}, ObjectColorLocation{}, TextAlphaLocation{};

	void Translate(GLfloat MoveX, GLfloat MoveY);
	void Rotate(GLfloat Radians);
	void Scale(GLfloat ScaleX, GLfloat ScaleY);
	void RotateSpot(GLfloat Radians);
	void RotateAxis(GLfloat Radians, GLfloat AxisX, GLfloat AxisY);
	void SetColor(GLfloat R, GLfloat G, GLfloat B);
	void SetAlpha(GLfloat Value);
	void InitTransform();

	virtual void Update(float FT) {}
	virtual void InputMouse(bool LButtonDown, bool RButtonDown) {}
	virtual void InputKey(unsigned char KEY, bool KeyDown) {}
	virtual void InputSpecialKey(int KEY, bool KeyDown) {}
	virtual void Render() {}
	virtual ~OBJ_BASE() {}
	void ProcessTransform();

	virtual void ResetControlState() {}
	
	///////////////

	virtual void SetGenTime(GLfloat TimeValue) {}
	virtual GLfloat GetRotation() { return{}; }
};

// dummy object for avoiding iterator errors
class FWM_DUMMY : public OBJ_BASE {};