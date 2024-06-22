#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "GLHeader.h"

class ShaderUtil {
private:
	GLchar *vertex_source{}, *fragment_source{};
	GLuint vertex_shader{}, fragment_shader{};

public:
	char* LoadBuffer(const char* file);
	void LoadVertexShader(const char* VertexShader);
	void LoadFragmentShader(const char* FragmentShader);
	void CreateShader(GLuint& Shader);
};
extern ShaderUtil shader;