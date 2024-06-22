#pragma once
#include "GLHeader.h"
#include <string>
#include <unordered_map>

class ImageUtil {
private:
	GLuint VAO{};
	std::unordered_map<std::string, unsigned int> LoadedImageList;

public:
	void Init();
	void LoadImageFromList();
	unsigned int SetImage(std::string ImageName);
	void Draw(unsigned int ImageVar);
};
extern ImageUtil imageUtil;