#ifndef YAUI_BUFFER_H
#define YAUI_BUFFER_H


#include <GLES2/gl2.h>
#include "Types.h"

namespace yaui::gles2 {
    struct BufferLayoutElement {
        String attribute;
        GLuint location;
        GLint size;
        GLenum type;
        GLint isNormalised;
        uint32 offset;
    } __attribute__((aligned(64)));
    using BufferLayout = std::vector<BufferLayoutElement>;

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


#endif //YAUI_BUFFER_H
