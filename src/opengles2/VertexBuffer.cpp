#include "VertexBuffer.h"
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
