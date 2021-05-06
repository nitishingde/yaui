#include "Buffer.h"
#include "Utility.h"

yaui::gles2::VertexBuffer::VertexBuffer(const void *pData, GLsizei stride, uint32 size, const VertexBufferLayout &vertexBufferLayout)
    : mId(0)
    , mVertexBufferLayout(vertexBufferLayout)
    , mStride(stride) {
    init(pData, stride, size, vertexBufferLayout);
}

yaui::gles2::VertexBuffer::~VertexBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

void yaui::gles2::VertexBuffer::init(const void *pData, GLsizei stride, yaui::uint32 size, const yaui::gles2::VertexBufferLayout &vertexBufferLayout) {
    mStride = stride;
    mVertexBufferLayout = vertexBufferLayout;
    if(glIsBuffer(mId) == GL_FALSE) {
        debugGlCall(glGenBuffers(1, &mId));
    }
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(size * stride), pData, GL_DYNAMIC_DRAW));
}

const yaui::gles2::VertexBufferLayout& yaui::gles2::VertexBuffer::getLayout() const {
    return mVertexBufferLayout;
}

void yaui::gles2::VertexBuffer::bind() const {
    for(const auto &layout: mVertexBufferLayout) {
        debugGlCall(glEnableVertexAttribArray(layout.location));
        debugGlCall(glVertexAttribPointer(layout.location, layout.size, layout.type, layout.isNormalised, mStride, (void*)layout.offset));
    }
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, mId));
}

void yaui::gles2::VertexBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

yaui::gles2::VertexArrayBuffer::VertexArrayBuffer() {
    debugGlCall(glGenBuffers(1, &mId));
}

yaui::gles2::VertexArrayBuffer::VertexArrayBuffer(std::vector<uint32> &&vertexArray)
    : mVertexArray(std::move(vertexArray)) {
    debugGlCall(glGenBuffers(1, &mId));
}

yaui::gles2::VertexArrayBuffer::~VertexArrayBuffer() {
    debugGlCall(glDeleteBuffers(1, &mId));
}

std::vector<yaui::uint32>& yaui::gles2::VertexArrayBuffer::getVertexArray() {
    return mVertexArray;
}

void yaui::gles2::VertexArrayBuffer::setVertexArray(std::vector<uint32> &&vertexArray) {
    mVertexArray = std::move(vertexArray);
}

void yaui::gles2::VertexArrayBuffer::bind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId));
    debugGlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mVertexArray.size()*sizeof(uint32), mVertexArray.data(), GL_DYNAMIC_DRAW));
}

void yaui::gles2::VertexArrayBuffer::unbind() const {
    debugGlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

yaui::uint32 yaui::gles2::VertexArrayBuffer::getSize() const {
    return mVertexArray.size();
}

GLenum yaui::gles2::VertexArrayBuffer::getType() const {
    return GL_UNSIGNED_INT;
}
