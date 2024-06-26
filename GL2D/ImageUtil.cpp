#include "ImageUtil.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// image list to load
std::unordered_map<std::string, const char*> ImageList
{
	{"gl2d_boundbox", "GL2D res//boundbox.png"}, // do not delete this

	// play mode
	{"center_triangle", "resources//image//shape//center_triangle.png"},
	{"center_square", "resources//image//shape//center_square.png"},
	{"center_pentagon", "resources//image//shape//center_pentagon.png"},
	{"center_hexagon", "resources//image//shape//center_hexagon.png"},

	{"obstacle_triangle_1", "resources//image//obstacles//obstacle_triangle_1.png"},
	{"obstacle_square_1", "resources//image//obstacles//obstacle_square_1.png"},
	{"obstacle_pentagon_1", "resources//image//obstacles//obstacle_pentagon_1.png"},
	//{"obstacle_hexagon", "resources//image//obstacles//obstacle_hexagon.png"},
	{"feedback", "resources//image//shape//feedback.png"},

	{"score_plate", "resources//image//ui//score_plate.png"},

	// lobby mode
	{"arrow_right", "resources//image//ui//arrow_right.png"},
	{"arrow_left", "resources//image//ui//arrow_left.png"},
	{"button_info", "resources//image//ui//button_info.png"},
	{"button_sound_enable", "resources//image//ui//button_sound_enable.png"},
	{"button_sound_disable", "resources//image//ui//button_sound_disable.png"},

	// cursor
	{"cursor", "resources//image//ui//cursor.png"},
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