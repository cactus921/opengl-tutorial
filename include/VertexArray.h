#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H


#include "VertexBuffer.h"


class VertexBufferLayout;

class VertexArray
{
    private:
        void Release();
        unsigned int m_RendererID;

    public:
        VertexArray();
        //virtual ~VertexArray();
        virtual ~VertexArray() {Release();};
        VertexArray(const VertexArray &) = delete;
        VertexArray &operator=(const VertexArray &) = delete;
        VertexArray(VertexArray &&other)  :   m_RendererID(other.m_RendererID)
        {
            other.m_RendererID = 0;
        }
        VertexArray &operator=(VertexArray &&other)
        {
            if(this != &other)
            {
                Release();
                m_RendererID = other.m_RendererID;
                other.m_RendererID = 0;
            }
            return *this;
        }

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void Bind() const;
        void Unbind() const;

    protected:

    
};

#endif // VERTEXARRAY_H
