#include "ImageUtil.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// image list to load
std::unordered_map<std::string, const char*> ImageList
{
	{"gl2d_boundbox", "GL2D res//boundbox.png"}, // do not delete this
	{"image", "image.png"}
};


GLfloat ImagePannel[][48] = {  // default size 1.0 * 1.0
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 0.0,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 1.0,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0, 0.0
};


void ImageUtil::Init() {
	GLuint VBO{};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(ImagePannel), ImagePannel, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(true);

	LoadImageFromList();
}

void ImageUtil::LoadImageFromList() {
	for (auto& [Name, File] : ImageList) {
		unsigned int Image{};
		int Width{}, Height{}, Channel{};

		glGenTextures(1, &Image);
		glBindTexture(GL_TEXTURE_2D, Image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* texture_data = stbi_load(File, &Width, &Height, &Channel, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
		stbi_image_free(texture_data);

		LoadedImageList.insert(std::pair(Name, Image));
	}
}

unsigned int ImageUtil::SetImage(std::string ImageName) {
	return LoadedImageList.find(ImageName)->second;
}

GLfloat ImageUtil::Aspect(int Width, int Height) {
	return Width / Height;
}

void ImageUtil::Draw(unsigned int ImageVar) {
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, ImageVar);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}