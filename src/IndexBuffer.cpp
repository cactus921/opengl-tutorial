#include "IndexBuffer.h"
#include "Renderer.h"
#include "DebugManager.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    //ctor
    m_Count = count;
    GLCALL(glGenBuffers(1, &m_RendererID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    //GLDebugOut("Index Buffer created, with ID", m_RendererID);
}
/*
IndexBuffer::~IndexBuffer()
{
    //dtor
    GLCALL(glDeleteBuffers(1, &m_RendererID));
}
*/

void IndexBuffer::Release()
{
    //dtor
    GLCALL(glDeleteBuffers(1, &m_RendererID));
    //GLDebugOut("Index Buffer deleted, with ID", m_RendererID);
    m_RendererID = 0;
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    //GLDebugOut("Index Buffer bound, with ID", m_RendererID);
}


void IndexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    //GLDebugOut("Index Buffer unbound, with ID", m_RendererID);
}
