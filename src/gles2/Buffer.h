#ifndef YAUI_BUFFER_H
#define YAUI_BUFFER_H


#include <GLES2/gl2.h>
#include <glm/glm.hpp>
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
        GLuint mId = 0;
        BufferLayout mBufferLayout{};
        GLsizei mStride = 0;

    public:
        explicit VertexBuffer() = default;
        explicit VertexBuffer(const void *pData, GLsizei stride, uint32 size, const BufferLayout &bufferLayout);
        ~VertexBuffer();
        VertexBuffer(const VertexBuffer &other) = delete;
        VertexBuffer& operator=(const VertexBuffer &other) = delete;
        VertexBuffer(VertexBuffer &&other) = default;
        VertexBuffer& operator=(VertexBuffer &&other) = default;
        void init(const void *pData, GLsizei stride, uint32 size, const BufferLayout &bufferLayout);
        [[nodiscard]] const BufferLayout& getLayout() const;
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
        VertexArrayBuffer(const VertexArrayBuffer &other) = delete;
        VertexArrayBuffer& operator=(const VertexArrayBuffer &other) = delete;
        VertexArrayBuffer(VertexArrayBuffer &&other) = delete;
        VertexArrayBuffer& operator=(VertexArrayBuffer &&other) = delete;
        void bind() const;
        void unbind() const;
        [[nodiscard]] int32 getSize() const;
        [[nodiscard]] GLenum getType() const;
    };

    struct PixelVertex {
        glm::vec2 position;
        glm::vec4 colour;
    } __attribute__((aligned(32)));

    struct PixelVertices {
        yaui::gles2::BufferLayout bufferLayout;
        yaui::gles2::VertexBuffer vertexBuffer;
        std::vector<PixelVertex> vertexData;
    } __attribute__((aligned(128)));
}


#endif //YAUI_BUFFER_H
