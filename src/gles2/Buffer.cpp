#include "Buffer.h"
#include "Utility.h"

yaui::gles2::VertexBuffer::VertexBuffer(const void *pData, GLsizei stride, uint32 size, const BufferLayout &bufferLayout)
    : mId(0)
    , mBufferLayout(bufferLayout)
    , mStride(stride) {
    init(pData, stride, size, bufferLayout);
}

yaui::gles2::VertexBuffer::~VertexBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

void yaui::gles2::VertexBuffer::init(const void *pData, GLsizei stride, yaui::uint32 size, const yaui::gles2::BufferLayout &bufferLayout) {
    mStride = stride;
    mBufferLayout = bufferLayout;
    if(glIsBuffer(mId) == GL_FALSE) {
        debugGlCall(glGenBuffers(1, &mId));
    }
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(size * stride), pData, GL_DYNAMIC_DRAW));
}

const yaui::gles2::BufferLayout& yaui::gles2::VertexBuffer::getLayout() const {
    return mBufferLayout;
}

void yaui::gles2::VertexBuffer::bind() const {
    for(const auto &layout: mBufferLayout) {
        debugGlCall(glEnableVertexAttribArray(layout.location));
        debugGlCall(glVertexAttribPointer(layout.location, layout.size, layout.type, layout.isNormalised, mStride, (void*)layout.offset));
    }
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
}

void yaui::gles2::VertexBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

yaui::gles2::VertexArrayBuffer::VertexArrayBuffer(const uint32 *pData, int32 size)
    : mId(0)
    , mSize(size) {
    debugGlCall(glGenBuffers(1, &mId));
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize*sizeof(uint32), pData, GL_DYNAMIC_DRAW));
}

yaui::gles2::VertexArrayBuffer::~VertexArrayBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

void yaui::gles2::VertexArrayBuffer::bind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
}

void yaui::gles2::VertexArrayBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

yaui::int32 yaui::gles2::VertexArrayBuffer::getSize() const {
    return mSize;
}

GLenum yaui::gles2::VertexArrayBuffer::getType() const {
    return GL_UNSIGNED_INT;
}
