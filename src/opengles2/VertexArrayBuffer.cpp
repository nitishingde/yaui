#include "VertexArrayBuffer.h"
#include "Utility.h"

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
