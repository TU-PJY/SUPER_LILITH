#pragma once
#include "ImageUtil.h"

class Triangle {
private:
	unsigned int Image{};

public:
	void Init() {
		Image = imageUtil.SetImage("center_triangle");
	}

	void Render() {
		imageUtil.Draw(Image);
	}
};

class Square {
private:
	unsigned int Image{};

public:
	void Init() {
		Image = imageUtil.SetImage("center_square");
	}

	void Render() {
		imageUtil.Draw(Image);
	}
};


class Pentagon {
private:
	unsigned int Image{};

public:
	void Init() {
		Image = imageUtil.SetImage("center_pentagon");
	}

	void Render() {
		imageUtil.Draw(Image);
	}
};

class Hexagon {
private:
	unsigned int Image{};

public:
	void Init() {
		Image = imageUtil.SetImage("center_hexagon");
	}

	void Render() {
		imageUtil.Draw(Image);
	}
};
