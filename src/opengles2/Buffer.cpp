#include "Buffer.h"
#include "Utility.h"

yaui::VertexBuffer::VertexBuffer(const void *pData, GLsizei stride, uint32 size, const BufferLayout &bufferLayout)
    : mId(0)
    , mBufferLayout(bufferLayout)
    , mStride(stride) {
    debugGlCall(glGenBuffers(1, &mId));
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(size * stride), pData, GL_DYNAMIC_DRAW));
}

yaui::VertexBuffer::~VertexBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

const yaui::BufferLayout& yaui::VertexBuffer::getLayout() const {
    return mBufferLayout;
}

void yaui::VertexBuffer::bind() const {
    for(const auto &layout: mBufferLayout) {
        debugGlCall(glEnableVertexAttribArray(layout.location));
        debugGlCall(glVertexAttribPointer(layout.location, layout.size, layout.type, layout.isNormalised, mStride, (void*)layout.offset));
    }
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
}

void yaui::VertexBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

yaui::VertexArrayBuffer::VertexArrayBuffer(const uint32 *pData, int32 size)
    : mId(0)
    , mSize(size) {
    debugGlCall(glGenBuffers(1, &mId));
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize*sizeof(uint32), pData, GL_DYNAMIC_DRAW));
}

yaui::VertexArrayBuffer::~VertexArrayBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

void yaui::VertexArrayBuffer::bind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
}

void yaui::VertexArrayBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

yaui::int32 yaui::VertexArrayBuffer::getSize() const {
    return mSize;
}

GLenum yaui::VertexArrayBuffer::getType() const {
    return GL_UNSIGNED_INT;
}
