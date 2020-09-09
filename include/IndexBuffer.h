#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H



class IndexBuffer
{
    private:
        void Release();
        unsigned int m_RendererID;
        unsigned int m_Count;

    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        //virtual ~IndexBuffer();
        ~IndexBuffer() {Release();};
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer &operator=(const IndexBuffer&) = delete;
        IndexBuffer(IndexBuffer &&other)  :   m_RendererID(other.m_RendererID)
        {
            other.m_RendererID = 0;
        }
        IndexBuffer &operator=(IndexBuffer &&other)
        {
            if(this != &other)
            {
                Release();
                m_RendererID = other.m_RendererID;
                other.m_RendererID = 0;
                m_Count = other.m_Count;
            }
            return *this;
        }
        
        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount()  const { return m_Count; }

    protected:

};

#endif // INDEXBUFFER_H
