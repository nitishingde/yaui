#include "Texture.h"
#include "Utility.h"

yaui::gles2::Texture::Texture() {
    debugGlCall(glGenTextures(1, &mId));
}

yaui::gles2::Texture::~Texture() {
    debugGlCall(glDeleteTextures(1, &mId));
}

void yaui::gles2::Texture::bind(uint8 textureSlot) {
    mTextureSlot = GL_TEXTURE0 + textureSlot;
    debugGlCall(glActiveTexture(mTextureSlot));
    debugGlCall(glBindTexture(GL_TEXTURE_2D, mId));
}

void yaui::gles2::Texture::unbind() {
    debugGlCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void yaui::gles2::Texture::setTextureData(const uint8 *pPixelData, int32 width, int32 height, GLenum channelFormat) const {
    // set the texture wrapping/filtering options (on the currently bound texture object)
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    debugGlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    debugGlCall(glTexImage2D(GL_TEXTURE_2D, 0, channelFormat, width, height, 0, channelFormat, GL_UNSIGNED_BYTE, pPixelData));
}

yaui::int32 yaui::gles2::Texture::getTextureSlot() const {
    return int32(mTextureSlot - GL_TEXTURE0);
}
