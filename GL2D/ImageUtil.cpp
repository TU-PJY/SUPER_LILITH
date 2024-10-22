#include "ImageUtil.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// image list to load
std::unordered_map<std::string, const char*> ImageList
{
	{"gl2d_boundbox", "GL2D res//boundbox.png"}, // do not delete this
	{"FMOD_logo", "GL2D Res//FMOD Logo.png"},

	// play mode
	{"center_triangle", "resources//image//shape//center_triangle.png"},
	{"center_square", "resources//image//shape//center_square.png"},
	{"center_pentagon", "resources//image//shape//center_pentagon.png"},
	{"center_hexagon", "resources//image//shape//center_hexagon.png"},

	{"obstacle_triangle_1", "resources//image//obstacles//triangle//obstacle_triangle_1.png"},
	{"obstacle_triangle_2", "resources//image//obstacles//triangle//obstacle_triangle_2.png"},
	{"obstacle_triangle_3", "resources//image//obstacles//triangle//obstacle_triangle_3.png"},
	{"obstacle_triangle_4", "resources//image//obstacles//triangle//obstacle_triangle_4.png"},
	{"obstacle_triangle_5", "resources//image//obstacles//triangle//obstacle_triangle_5.png"},

	{"obstacle_square_1", "resources//image//obstacles//square//obstacle_square_1.png"},
	{"obstacle_square_2", "resources//image//obstacles//square//obstacle_square_2.png"},
	{"obstacle_square_3", "resources//image//obstacles//square//obstacle_square_3.png"},
	{"obstacle_square_4", "resources//image//obstacles//square//obstacle_square_4.png"},
	{"obstacle_square_5", "resources//image//obstacles//square//obstacle_square_5.png"},
	{"obstacle_square_6", "resources//image//obstacles//square//obstacle_square_6.png"},
	{"obstacle_square_7", "resources//image//obstacles//square//obstacle_square_7.png"},

	{"obstacle_pentagon_1", "resources//image//obstacles//pentagon//obstacle_pentagon_1.png"},
	{"obstacle_pentagon_2", "resources//image//obstacles//pentagon//obstacle_pentagon_2.png"},
	{"obstacle_pentagon_3", "resources//image//obstacles//pentagon//obstacle_pentagon_3.png"},
	{"obstacle_pentagon_4", "resources//image//obstacles//pentagon//obstacle_pentagon_4.png"},
	{"obstacle_pentagon_5", "resources//image//obstacles//pentagon//obstacle_pentagon_5.png"},
	{"obstacle_pentagon_6", "resources//image//obstacles//pentagon//obstacle_pentagon_6.png"},
	{"obstacle_pentagon_7", "resources//image//obstacles//pentagon//obstacle_pentagon_7.png"},

	{"feedback", "resources//image//shape//feedback.png"},

	{"score_plate", "resources//image//ui//score_plate.png"},

	// lobby mode
	{"arrow_right", "resources//image//ui//arrow_right.png"},
	{"arrow_left", "resources//image//ui//arrow_left.png"},
	{"button_info", "resources//image//ui//button_info.png"},
	{"button_effect_off", "resources//image//ui//button_effect_off.png"},
	{"button_effect_on", "resources//image//ui//button_effect_on.png"},
	{"button_music_reset_at_start", "resources//image//ui//button_music_reset_at_start.png"},
	{"button_music_resume_at_start", "resources//image//ui//button_music_resume_at_start.png"},
	{"button_data_reset", "resources//image//ui//button_data_reset.png"},

	{"bar", "resources//image//ui//bar.png"},
	{"icon_music_reset", "resources//image//ui//icon_music_restart.png"},
	{"icon_music_resume", "resources//image//ui//icon_music_resume.png"},
	{"icon_effect_on", "resources//image//ui//icon_effect_on.png"},
	{"icon_effect_off", "resources//image//ui//icon_effect_off.png"},

	// player face
	{"lilith_1", "resources//image//player//lilith_sprite_1.png"},
	{"lilith_2", "resources//image//player//lilith_sprite_2.png"},
	{"lilith_3", "resources//image//player//lilith_sprite_3.png"},
	{"lilith_4", "resources//image//player//lilith_sprite_4.png"},

	// player body
	{"lilith_body_1", "resources//image//player//lilith_sprite_body_1.png"},
	{"lilith_body_2", "resources//image//player//lilith_sprite_body_2.png"},
	{"lilith_body_3", "resources//image//player//lilith_sprite_body_3.png"},
	{"lilith_body_4", "resources//image//player//lilith_sprite_body_4.png"},
	{"lilith_body_5", "resources//image//player//lilith_sprite_body_5.png"},
	{"lilith_body_6", "resources//image//player//lilith_sprite_body_6.png"},
	{"lilith_body_7", "resources//image//player//lilith_sprite_body_7.png"},

	{"white_front", "resources//image//ui//white.png"},
	{"black_front", "resources//image//ui//black.png"},

	{"popup", "resources//image//ui//lobby_tutorial.png"},
	{"control_tut_left", "resources//image//ui//controltut_left.png"},
	{"control_tut_right", "resources//image//ui//controltut_right.png"},
	{"control_tut_lshift", "resources//image//ui//controltut_l_shift.png"},
	{"control_tut_rshift", "resources//image//ui//controltut_r_shift.png"},

	{"fanfare", "resources//image//ui//fanfare.png"},

	// logo
	{"logo", "resources//image//ui//mata_logo.png"}
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

void ImageUtil::LoadImageFromFile(std::string Name, const char* FileName) {
	unsigned int Image{};
	int Width{}, Height{}, Channel{};

	glGenTextures(1, &Image);
	glBindTexture(GL_TEXTURE_2D, Image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* texture_data = stbi_load(FileName, &Width, &Height, &Channel, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
	stbi_image_free(texture_data);

	LoadedImageList.insert(std::pair(Name, Image));
}

unsigned int ImageUtil::SetImage(std::string ImageName) {
	return LoadedImageList.lower_bound(ImageName)->second;
}

GLfloat ImageUtil::Aspect(float Width, float Height) {
	return Width / Height;
}

void ImageUtil::Draw(unsigned int ImageVar) {
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, ImageVar);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}