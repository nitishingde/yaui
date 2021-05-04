#include "Utility.h"
#include <fstream>
#include <spdlog/spdlog.h>

void yaui::glFlushErrors() {
    while(glGetError() != GL_NO_ERROR);
}

void yaui::glLogError(const char *file, int line) {
    for(GLenum errorCode = glGetError(); errorCode != GL_NO_ERROR; errorCode = glGetError()) {
        std::string error;
        switch(errorCode) {
            case GL_INVALID_ENUM:                   error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                  error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:              error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                  error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                                error = "UNKNOWN"; break;
        }
        spdlog::error("[OpenGL][file = {}][line = {}]: Error code = {}", file, line, error);
    }
}

yaui::String yaui::readFile(const String &filePath) {
    std::ifstream ifs(filePath);
    return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}

void yaui::loadImage(const char *imagePath, std::vector<uint8> &outPixelData, yaui::int32 &outWidth, yaui::int32 &outHeight, yaui::int32 &outChannels) {
    stbi_set_flip_vertically_on_load(1);
    auto image = stbi_load(imagePath, &outWidth, &outHeight, &outChannels, STBI_rgb_alpha);
    outChannels = 4;
    outPixelData.assign(image, image + outWidth * outHeight * outChannels);
    stbi_image_free(image);
}

void yaui::loadBasicAsciiFont(const char *fontPath, yaui::int32 fontSize, std::vector<uint8> &outPixelData, yaui::int32 &outWidth, yaui::int32 &outHeight, std::vector<stbtt_bakedchar> &bakedChars) {
    auto fontFile = yaui::readFile(fontPath);
    outWidth = 512, outHeight = fontSize;
    bakedChars.resize(95);
    int32 status = 0;
    do {
        outHeight += outHeight;
        outPixelData.resize(outWidth*outHeight);
        status = stbtt_BakeFontBitmap((unsigned char *)fontFile.data(), 0, float(fontSize), outPixelData.data(), outWidth, outHeight, 32, 95, bakedChars.data());
    } while (status <= 0);
    outWidth = 512;
    outHeight = status;
    outPixelData.resize(outWidth*outHeight);
    bakedChars.insert(bakedChars.begin(), 32, stbtt_bakedchar{0, 0, 0, 0, 0.f, 0.f, 0.f});
}
