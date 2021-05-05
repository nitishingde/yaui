#ifndef YAUI_TEXTURE_H
#define YAUI_TEXTURE_H


#include <GLES2/gl2.h>
#include "Types.h"

namespace yaui::gles2 {
    class Texture {
    private:
        GLuint mId{};
        int32 mWidth{};
        int32 mHeight{};
        int32 mChannels{};
        GLint mFormat;
        std::vector<uint8> mPixelData;

    public:
        explicit Texture(uint8 *pixelData, int32 width, int32 height, int32 channels, GLint format);
        ~Texture();
        Texture(const Texture &other) = delete;
        Texture& operator=(const Texture &other) = delete;
        Texture(Texture &&other) = delete;
        Texture& operator=(Texture &&other) = delete;
        void bind();
        void unbind();
    };
}


#endif //YAUI_TEXTURE_H
