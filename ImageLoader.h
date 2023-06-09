#pragma once

#include <gl/glew.h>
#include <string>

class ImageLoader
{
	GLuint id;
public:
	//ImageLoader(const std::string& fileName);
	//void bind();
	bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
};