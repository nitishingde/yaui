#include "VertexBuffer.h"
#include <GLES2/gl2.h>
#include "Utility.h"

yaui::VertexBuffer::VertexBuffer(const void *pData, uint32 byteSize)
    : mId(0) {
    debugGlCall(glGenBuffers(1, &mId));
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(byteSize), pData, GL_DYNAMIC_DRAW));
}

yaui::VertexBuffer::~VertexBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

void yaui::VertexBuffer::bind() const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
}

void yaui::VertexBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
