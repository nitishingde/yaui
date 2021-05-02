#ifndef YAUI_UTILITY_H
#define YAUI_UTILITY_H


#include "Types.h"

#if NDEBUG
#define debugGlCall(x) x
#else
#define debugGlCall(x)                  \
yaui::glFlushErrors();                  \
x;                                      \
yaui::glLogError(__FILE__, __LINE__)
#endif

namespace yaui {
    void glFlushErrors();
    void glLogError(const char *file, int line);
    String readFile(const String &filePath);
    void loadImage(const char *imagePath, std::vector<uint8> &outPixelData, yaui::int32 &outWidth, yaui::int32 &outHeight, yaui::int32 &outChannels);
}

#endif //YAUI_UTILITY_H
