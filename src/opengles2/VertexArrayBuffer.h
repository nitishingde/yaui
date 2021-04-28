#ifndef YAUI_VERTEXARRAYBUFFER_H
#define YAUI_VERTEXARRAYBUFFER_H


#include "Types.h"

namespace yaui {
    class VertexArrayBuffer {
    private:
        GLuint mId;
        int32 mSize;

    public:
        explicit VertexArrayBuffer(const uint32 *pData, int32 size);
        ~VertexArrayBuffer();
        void bind() const;
        void unbind() const;
        int32 getSize() const;
        GLenum getType() const;
    };
}


#endif //YAUI_VERTEXARRAYBUFFER_H
