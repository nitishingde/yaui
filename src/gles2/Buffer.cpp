#include "Buffer.h"
#include "Utility.h"

yaui::gles2::VertexBuffer::VertexBuffer() {
    debugGlCall(glGenBuffers(1, &mId));
}

yaui::gles2::VertexBuffer::VertexBuffer(const void *pData, uint32 byteSize) {
    debugGlCall(glGenBuffers(1, &mId));
    setData(pData, byteSize);
}

yaui::gles2::VertexBuffer::~VertexBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

void yaui::gles2::VertexBuffer::setData(const void *pData, uint32 byteSize) const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ARRAY_BUFFER, byteSize, pData, GL_DYNAMIC_DRAW));
}

void yaui::gles2::VertexBuffer::bind() const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
}

void yaui::gles2::VertexBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

yaui::gles2::VertexArrayBuffer::VertexArrayBuffer() {
    debugGlCall(glGenBuffers(1, &mId));
}

yaui::gles2::VertexArrayBuffer::VertexArrayBuffer(const std::vector<uint32> &vertexArray) {
    debugGlCall(glGenBuffers(1, &mId));
    setBufferData(vertexArray);
}

yaui::gles2::VertexArrayBuffer::~VertexArrayBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

void yaui::gles2::VertexArrayBuffer::setBufferData(const std::vector<uint32> &vertexArray) {
    mCount = vertexArray.size();
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexArray.size()*sizeof(uint32), vertexArray.data(), GL_DYNAMIC_DRAW));
}

void yaui::gles2::VertexArrayBuffer::bind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
}

void yaui::gles2::VertexArrayBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

yaui::uint32 yaui::gles2::VertexArrayBuffer::getCount() const {
    return mCount;
}

GLenum yaui::gles2::VertexArrayBuffer::getType() const {
    return GL_UNSIGNED_INT;
}
