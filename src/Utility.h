#ifndef YAUI_UTILITY_H
#define YAUI_UTILITY_H


#include "GLES2/gl2.h"
#include "yaui_stb.h"
#include "Types.h"

#if NDEBUG

#define debugGlCall(x) x

#define YAUI_LOG_INFO(...)
#define YAUI_LOG_ERROR(...)

#define YAUI_EXPECTS(predicate, exception)
#define YAUI_ENSURES(predicate, exception)

#define YAUI_ASSERT(x)

#else

#define debugGlCall(x)                  \
yaui::glFlushErrors();                  \
x;                                      \
yaui::glLogError(__FILE__, __LINE__)

#include <spdlog/spdlog.h>
// use info for normal starting/stopping of services, and error is hopefully self explanatory
#define YAUI_LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define YAUI_LOG_ERROR(...) spdlog::error(__VA_ARGS__)

// use this in places where client is responsible (like public member functions etc.)
// pre checking
#define YAUI_EXPECTS(predicate, exception) if(!(predicate)) throw exception
// post checking
#define YAUI_ENSURES(predicate, exception) if(!(predicate)) throw exception

#include <cassert>
// use this in places where client is not responsible (like private member functions etc.)
#define YAUI_ASSERT(x) assert((x))

#endif

namespace yaui {
    void glFlushErrors();
    void glLogError(const char *file, int line);
    std::string readFile(const char *filePath);
    void loadImage(const char *imagePath, std::vector<uint8> &outPixelData, yaui::int32 &outWidth, yaui::int32 &outHeight, yaui::int32 &outChannels);
    void loadBasicAsciiFont(const char *fontPath, yaui::int32 fontSize, std::vector<uint8> &outPixelData, yaui::int32 &outWidth, yaui::int32 &outHeight, std::vector<stbtt_bakedchar> &bakedChars);
}

#endif //YAUI_UTILITY_H
