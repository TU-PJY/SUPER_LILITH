#include "ShaderUtil.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

GLuint ImageShader;
GLuint TextShader;

char* ShaderUtil::LoadBuffer(const char* FileName) {
	FILE* File{};
	long Length{};
	char* Buffer{};

	File = fopen(FileName, "rb");
	if (!File)
		return NULL;

	fseek(File, 0, SEEK_END);

	Length = ftell(File);
	Buffer = (char*)malloc(Length + 1);

	fseek(File, 0, SEEK_SET);
	fread(Buffer, Length, 1, File);
	fclose(File);

	Buffer[Length] = 0;

	return Buffer;
}

void ShaderUtil::LoadVertexShader(const char* VertexShader) {
	vertex_source = LoadBuffer(VertexShader);
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const GLchar**)&vertex_source, 0);
	glCompileShader(vertex_shader);

	GLint Result{};
	GLchar ErrorLog[512]{};

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &Result);

	if (!Result) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, ErrorLog);
		std::cout << "ERROR: vertex shader err\n" << ErrorLog << std::endl;

		return;
	}
}

void ShaderUtil::LoadFragmentShader(const char* FragmentShader) {
	fragment_source = LoadBuffer(FragmentShader);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const GLchar**)&fragment_source, 0);
	glCompileShader(fragment_shader);

	GLint Result{};
	GLchar ErrorLog[512]{};

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &Result);

	if (!Result) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, ErrorLog);
		std::cout << "ERROR: fragment shader err\n" << ErrorLog << std::endl;

		return;
	}
}

void ShaderUtil::CreateShader(GLuint& Shader) {
	Shader = glCreateProgram();
	glAttachShader(Shader, vertex_shader);
	glAttachShader(Shader, fragment_shader);

	glLinkProgram(Shader);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glUseProgram(Shader);
}