#include <iostream>
#include "Texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int width, height, nrChannels;
unsigned char* data;

Texture::Texture(const std::string& fileName)
{
    data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 4);
}

void Texture::bind()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // std::cout << "Succeeded loading" << std::endl;
    }
    else {
        std::cout << "Failed loading" << std::endl;
    }

    stbi_image_free(data);
}