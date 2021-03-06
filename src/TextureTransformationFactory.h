#ifndef YAUI_TEXTURETRANSFORMATIONFACTORY_H
#define YAUI_TEXTURETRANSFORMATIONFACTORY_H


#include "TextureTransformation.h"

namespace yaui {
    class TextureTransformationFactory {
    public:
        static TextureTransformation produceAddBackgroundColourTextureTransformation();
        static TextureTransformation produceAddBorderTextureTransformation();
        static TextureTransformation produceAddLabelTextureTransformation();
        static TextureTransformation produceAddTextFieldTextureTransformation();
    };
}


#endif //YAUI_TEXTURETRANSFORMATIONFACTORY_H
