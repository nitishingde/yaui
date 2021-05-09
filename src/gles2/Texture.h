#ifndef YAUI_TEXTURE_H
#define YAUI_TEXTURE_H


#include <GLES2/gl2.h>
#include "Types.h"

namespace yaui::gles2 {
    class Texture {
    private:
        GLuint mId{};
        GLenum mTextureSlot = GL_TEXTURE0;

    public:
        explicit Texture();
        ~Texture();
        Texture(const Texture &other) = delete;
        Texture& operator=(const Texture &other) = delete;
        Texture(Texture &&other) = delete;
        Texture& operator=(Texture &&other) = delete;
        void bind(uint8 textureSlot = 0);
        void unbind();
        void setTextureData(const uint8 *pPixelData, int32 width, int32 height, GLenum channelFormat = GL_RGBA) const;
        [[nodiscard]] int32 getTextureSlot() const;
    };
}


#endif //YAUI_TEXTURE_H
