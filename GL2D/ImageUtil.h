#pragma once
#include "GLHeader.h"
#include <string>
#include <unordered_map>
#include <map>

class ImageUtil {
private:
	GLuint VAO{};
	std::map<std::string, unsigned int> LoadedImageList;

public:
	void Init();
	void LoadImageFromList();
	void LoadImageFromFile(std::string Name, const char* FileName);
	unsigned int SetImage(std::string ImageName);
	GLfloat Aspect(float Width, float Height);
	void Draw(unsigned int ImageVar);
};
extern ImageUtil imageUtil;