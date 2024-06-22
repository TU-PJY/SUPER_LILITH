#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <string>
#include <cmath>

// display width, height and apsect ratio
extern int WIDTH, HEIGHT;
extern GLfloat ASPECT;

// corner position of display
struct Rect {
	GLfloat lx, ly, rx, ry;
};
extern Rect rect;

// GPU vendor name and vendor print option
extern std::string VENDOR;
constexpr bool PrintVendorInfoOpt = false;

// fullscreen option
constexpr bool StartWithFullScreen = false;

// boundbox option
constexpr bool ShowBoundBox = true;

// global scope shader
extern GLuint ImageShader;
extern GLuint TextShader;


// multiply Xposition with Aspect
inline GLfloat ASP(GLfloat ValueX) {
	return ValueX *= ASPECT;
}

// Divide Xposition with Aspect
inline GLfloat DivideASP(GLfloat ValueX) {
	return ValueX / ASPECT;
}

// Divide value with camera zoom value
inline GLfloat DivideZoom(GLfloat Value, GLfloat ZoomValue) {
	return Value / ZoomValue;
}

// Calculate distance of 2 dots
inline GLfloat GetDistance(GLfloat X1, GLfloat Y1, GLfloat X2, GLfloat Y2) {
	GLfloat DistanceX = X2 - X1;
	GLfloat DistanceY = Y2 - Y1;
	return sqrt(pow(DistanceX, 2) + pow(DistanceY, 2));
}