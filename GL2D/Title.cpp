#include "Title.h"
#include "ImageUtil.h"

Title::Title() {
	Image = imageUtil.SetImage("title");
	SetColor(1.0, 1.0, 1.0);
}

void Title::Update(float FT) {
	InitTransform();

	Scale(0.8, 0.8);
	Scale(imageUtil.Aspect(1500, 500), 1.0);

	Translate(0.0, 0.7);
}

void Title::Render() {
	ProcessTransform();
	imageUtil.Draw(Image);
}
