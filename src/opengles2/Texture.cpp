#include "Texture.h"
#include "stb_image.h"
#include "Utility.h"

yaui::Texture::Texture() {
    debugGlCall(glGenTextures(1, &mId));
}

yaui::Texture::~Texture() {
    debugGlCall(glDeleteTextures(1, &mId));
}

void yaui::Texture::loadImage(const char *imagePath) {
    stbi_set_flip_vertically_on_load(1);
    auto image = stbi_load(imagePath, &mWidth, &mHeight, &mChannels, STBI_rgb_alpha);
    mChannels = 4;
    mPixelData.assign(image, image + mWidth*mHeight*mChannels);
    stbi_image_free(image);
}

void yaui::Texture::bind() {
    debugGlCall(glBindTexture(GL_TEXTURE_2D, mId));
    // set the texture wrapping/filtering options (on the currently bound texture object)
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    debugGlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixelData.data()));
}

void yaui::Texture::unbind() {
    debugGlCall(glBindTexture(GL_TEXTURE_2D, 0));
}

std::tuple<float, float> yaui::Texture::getDimension() const {
    return {float(mWidth), float(mHeight)};
}
