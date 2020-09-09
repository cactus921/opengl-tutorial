#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "DebugManager.h"

VertexArray::VertexArray()
{
    //ctor
    GLCALL(glGenVertexArrays(1, &m_RendererID));
    //GLDebugOut("Vertex Array created, with ID", m_RendererID);
}

/*
VertexArray::~VertexArray()
{
    //dtor
    GLCALL(glDeleteVertexArrays(1, &m_RendererID));
}
*/

void VertexArray::Release()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
    //GLDebugOut("Vertex Array deleted, with ID", m_RendererID);
    m_RendererID = 0;
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i=0; i<elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCALL(glEnableVertexAttribArray(i));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(m_RendererID));
    //GLDebugOut("Vertex Array bound, with ID", m_RendererID);
}


void VertexArray::Unbind() const
{
    GLCALL(glBindVertexArray(0));
    //GLDebugOut("Vertex Array unbound, with ID", m_RendererID);
}

