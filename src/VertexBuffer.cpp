#include "VertexBuffer.h"
#include "Renderer.h"
#include "DebugManager.h"

/*
VertexBuffer::VertexBuffer()
{
    //ctor
    GLCALL(glGenBuffers(1, &m_RendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    //GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
*/

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //ctor
    GLCALL(glGenBuffers(1, &m_RendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    //GLDebugOut("Vertex Buffer created, with ID", m_RendererID);
}

/*
VertexBuffer::~VertexBuffer()
{
    //dtor
    GLCALL(glDeleteBuffers(1, &m_RendererID));
}
*/

void VertexBuffer::Release()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
    //GLDebugOut("Vertex Buffer deleted, with ID", m_RendererID);
    m_RendererID = 0;
}

void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    //GLDebugOut("Vertex Buffer bound, with ID", m_RendererID);
}


void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    //GLDebugOut("Vertex Buffer unbound, with ID", m_RendererID);
}
