#include "GLHeader.h"
#include "ShaderUtil.h"
#include "CameraUtil.h"
#include "RenderModeUtil.h"
#include "ImageUtil.h"
#include "TextUtil.h"
#include "MouseUtil.h"
#include "SoundUtil.h"
#include "DataUtil.h"
#include "FontLoaderUtil.h"
#include "FWM.h"

#include "Stage1.h"
#include "Lobby.h"
#include "Intro.h"
#include "Splash.h"

#include "MusicPlayer.h"

#include <iostream>
#include <map>
#include <ctime>

int WIDTH = 800;
int HEIGHT = 400;

glm::vec3 BackgroundColor = glm::vec3(0.0, 0.0, 0.0);

void SetBackgroundColor(GLfloat R, GLfloat G, GLfloat B) {
	BackgroundColor.r = R;
	BackgroundColor.g = G;
	BackgroundColor.b = B;
}

GLfloat ASPECT;
Rect rect;

int Face = lilith;
int PrevSec;
int PrevMil;
bool TitleInit;

std::string VENDOR;

ShaderUtil shader;
CameraUtil cam;
CameraControlUtil camUtil;
RenderModeUtil renderMode;
ImageUtil imageUtil;
TextUtilUnicode textUnicode;
MouseUtil mouse;
SoundUtil soundUtil;
DataUtil dataUtil;
FontLoaderUtil fontloaderUtil;
FWM fw;

MusicPlayer mp;

clock_t StartTime, EndTime;
float FrameTime;


GLvoid DisplayReshape(int w, int h) {
	glViewport(0, 0, w, h);
	WIDTH = w;
	HEIGHT = h;
}

GLvoid GLMain() {
	StartTime = clock();

	glClearColor(BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	soundUtil.Update();
	mp.Update();
	camUtil.UpdateZoom(FrameTime);
	
	fw.Routine();

	glutSwapBuffers();
	glutPostRedisplay();

	EndTime = clock();
	FrameTime = float(EndTime - StartTime) / 1000;
	fw.SetFrameTime(FrameTime);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GL_MULTISAMPLE);

	glutInitWindowPosition(GetSystemMetrics(SM_CXSCREEN) / 2 - WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - HEIGHT / 2);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("GL2D");

	glutSetCursor(GLUT_CURSOR_NONE);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Unable to initialize GLEW\n\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n\n";

	const GLubyte* VecdorInfo = glGetString(GL_VENDOR);
	if (VecdorInfo) {
		VENDOR = reinterpret_cast<const char*>(VecdorInfo);
		if (PrintVendorInfoOpt)
			std::cout << "GPU Vendor: " << VENDOR << "\n\n";
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader.LoadVertexShader("GLSL//GLSL_vertex.glsl");
	shader.LoadFragmentShader("GLSL//GLSL_fragment.glsl");
	shader.CreateShader(ImageShader);

	shader.LoadFragmentShader("GLSL//GLSL_fragment_text.glsl");
	shader.CreateShader(TextShader);

	DWORD dword{};
	fontloaderUtil.ImportFont("resources//font//GALSB.ttf", dword);
	imageUtil.Init();
	fw.Init(Splash::SplashMode, Splash::SetController);

	// for dev
	/*glutFullScreen();
	imageUtil.LoadImageFromList();
	soundUtil.Init();
	dataUtil.Init();
	fw.Init(Lobby::LobbyMode, Lobby::SetController);*/


	glutDisplayFunc(GLMain);
	glutReshapeFunc(DisplayReshape);
	glutMainLoop();
}