#ifndef YAUI_VERTEXBUFFER_H
#define YAUI_VERTEXBUFFER_H


#include "Types.h"

namespace yaui {
    class VertexBuffer {
    private:
        GLuint mId;
        BufferLayout mBufferLayout;
        GLsizei mStride;

    public:
        explicit VertexBuffer(const void *pData, GLsizei stride, uint32 size, const BufferLayout &bufferLayout);
        ~VertexBuffer();
        const BufferLayout& getLayout() const;
        void bind() const;
        void unbind() const;
    };
}


#endif //YAUI_VERTEXBUFFER_H
