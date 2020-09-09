#ifndef TEXTURE_H
#define TEXTURE_H

#include "DebugManager.h"

class Texture
{
    protected:

    private:
        void Release();
        unsigned int m_RendererID, m_texSlot;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;

    public:
        Texture(const std::string& filePath);
        //virtual ~Texture();
        ~Texture() {Release();};
        Texture(const Texture&) = delete;
        Texture &operator = (const Texture &) = delete;
        Texture(Texture &&other)  :   m_RendererID(other.m_RendererID)
        {
            other.m_RendererID = 0;
        }
        Texture &operator = (Texture &&other)
        {
            if(this != &other)
            {
                Release();
                m_RendererID = other.m_RendererID;
                other.m_RendererID = 0;
                m_LocalBuffer = other.m_LocalBuffer;
                other.m_LocalBuffer = nullptr;
                m_Width = other.m_Width;
                m_Height = other.m_Height;
                m_BPP = other.m_BPP;
                
            }
            return *this;
        }
        
        void Bind();
        void Bind(unsigned int slot);
        void Unbind() const;

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

    

};

#endif // TEXTURE_H
