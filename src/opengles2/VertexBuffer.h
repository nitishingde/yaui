#ifndef YAUI_VERTEXBUFFER_H
#define YAUI_VERTEXBUFFER_H


#include <GLES2/gl2.h>
#include "Types.h"

namespace yaui {
    class VertexBuffer {
    private:
        GLuint mId;

    public:
        explicit VertexBuffer(const void *pData, uint32 byteSize);
        ~VertexBuffer();
        void bind() const;
        void unbind() const;
    };
}


#endif //YAUI_VERTEXBUFFER_H
