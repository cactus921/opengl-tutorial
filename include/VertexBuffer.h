#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H


class VertexBuffer
{
    private:
        void Release();
        unsigned int m_RendererID;

    public:
        //VertexBuffer();
        VertexBuffer(const void* data, unsigned int size);        
        ~VertexBuffer() {Release();};
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer &operator = (const VertexBuffer &) = delete;
        VertexBuffer(VertexBuffer &&other)  :   m_RendererID(other.m_RendererID)
        {
            other.m_RendererID = 0;
        }
        VertexBuffer &operator = (VertexBuffer &&other)
        {
            if(this != &other)
            {
                Release();
                m_RendererID = other.m_RendererID;
                other.m_RendererID = 0;
            }
            return *this;
        }
        
        void Bind() const;
        void Unbind() const;

    protected:


};

#endif // VERTEXBUFFER_H
