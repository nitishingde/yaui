#ifndef YAUI_TEXTURE_H
#define YAUI_TEXTURE_H


#include "Types.h"

namespace yaui {
    class Texture {
    private:
        GLuint mId{};
        int32 mWidth{};
        int32 mHeight{};
        int32 mChannels{};
        GLint mFormat;
        std::vector<uint8> mPixelData;

    public:
        explicit Texture(uint8 *pixelData = nullptr, int32 width = 0, int32 height = 0, int32 channels = 4, GLint format = GL_RGBA);
        ~Texture();
        void loadImage(const char *imagePath);
        void bind();
        void unbind();
        std::tuple<float, float> getDimension() const;
    };
}


#endif //YAUI_TEXTURE_H
