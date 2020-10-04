#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies/stb-master/stb_image.h"

TextureLoader::TextureLoader() {
}
TextureLoader::~TextureLoader() {
}

GLuint TextureLoader::getTextureID(std::string texFileName) {

	int width, height, channels;

	// Load the image data to an unsigned char pointer
	stbi_uc* image = stbi_load(texFileName.c_str(), &width, &height,
		&channels,
		STBI_rgb);

	// Generates and bind the texture
	GLuint mtexture;
	glGenTextures(1, &mtexture);
	glBindTexture(GL_TEXTURE_2D, mtexture);

	// Sets texture wrapping as GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Sets texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Sets mipmap values
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Creates the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	// Generates mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbinds the texture, free the picture and return
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
	return mtexture;
}