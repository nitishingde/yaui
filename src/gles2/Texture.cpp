#include "Texture.h"
#include "Utility.h"

yaui::gles2::Texture::Texture(yaui::uint8 *pixelData, yaui::int32 width, yaui::int32 height, yaui::int32 channels, GLint format)
    : mWidth(width)
    , mHeight(height)
    , mChannels(channels)
    , mFormat(format) {
    debugGlCall(glGenTextures(1, &mId));
    if(pixelData != nullptr) {
        mPixelData.assign(pixelData, pixelData + mWidth*mHeight*mChannels);
    }
}

yaui::gles2::Texture::~Texture() {
    debugGlCall(glDeleteTextures(1, &mId));
}

void yaui::gles2::Texture::bind() {
    debugGlCall(glBindTexture(GL_TEXTURE_2D, mId));
    // set the texture wrapping/filtering options (on the currently bound texture object)
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    debugGlCall(glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, mPixelData.data()));
}

void yaui::gles2::Texture::unbind() {
    debugGlCall(glBindTexture(GL_TEXTURE_2D, 0));
}
