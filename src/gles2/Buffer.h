#ifndef YAUI_BUFFER_H
#define YAUI_BUFFER_H


#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include "Types.h"

namespace yaui::gles2 {
    struct VertexBufferLayoutElement {
        String attribute;
        GLuint location;
        GLint size;
        GLenum type;
        GLint isNormalised;
        uint32 offset;
    } __attribute__((aligned(64)));
    using VertexBufferLayout = std::vector<VertexBufferLayoutElement>;

    class VertexBuffer {
    private:
        GLuint mId = 0;
        VertexBufferLayout mVertexBufferLayout{};
        GLsizei mStride = 0;

    public:
        explicit VertexBuffer() = default;
        explicit VertexBuffer(const void *pData, GLsizei stride, uint32 size, const VertexBufferLayout &vertexBufferLayout);
        ~VertexBuffer();
        VertexBuffer(const VertexBuffer &other) = delete;
        VertexBuffer& operator=(const VertexBuffer &other) = delete;
        VertexBuffer(VertexBuffer &&other) = default;
        VertexBuffer& operator=(VertexBuffer &&other) = default;
        void init(const void *pData, GLsizei stride, uint32 size, const VertexBufferLayout &vertexBufferLayout);
        [[nodiscard]] const VertexBufferLayout& getLayout() const;
        void bind() const;
        void unbind() const;
    };

    class VertexArrayBuffer {
    private:
        GLuint mId = 0;
        std::vector<uint32> mVertexArray{};

    public:
        explicit VertexArrayBuffer();
        explicit VertexArrayBuffer(std::vector<uint32> &&vertexArray);
        ~VertexArrayBuffer();
        VertexArrayBuffer(const VertexArrayBuffer &other) = delete;
        VertexArrayBuffer& operator=(const VertexArrayBuffer &other) = delete;
        VertexArrayBuffer(VertexArrayBuffer &&other) = delete;
        VertexArrayBuffer& operator=(VertexArrayBuffer &&other) = delete;
        std::vector<uint32>& getVertexArray();
        void setVertexArray(std::vector<uint32> &&vertexArray);
        void bind() const;
        void unbind() const;
        [[nodiscard]] uint32 getSize() const;
        [[nodiscard]] GLenum getType() const;
    };

    struct QuadVertex {
        glm::vec2 position;
        glm::vec4 colour;
    } __attribute__((aligned(32)));

    struct QuadVertexInfo {
        yaui::gles2::VertexBuffer vertexBuffer;
        std::vector<QuadVertex> quadVertices;
        // TODO: modify this, whenever gles2::QuadVertex gets modified
        yaui::gles2::VertexBufferLayout vertexBufferLayout {
            {"aPosition", 0, 2, GL_FLOAT, GL_FALSE, offsetof(gles2::QuadVertex, position)},
            {"aColour",   1, 4, GL_FLOAT, GL_FALSE, offsetof(gles2::QuadVertex, colour)},
        };
    } __attribute__((aligned(128)));
}


#endif //YAUI_BUFFER_H
