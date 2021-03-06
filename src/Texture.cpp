#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& filePath)
    : m_RendererID(0), m_FilePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    //ctor
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    GLCALL(glGenTextures(1, &m_RendererID));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    GLDebugOut("Bound Texture", m_RendererID);

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    if(m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);

}
/*
Texture::~Texture()
{
    //dtor
    GLCALL(glDeleteTextures(1, &m_RendererID));
}
*/
void Texture::Release()
{
    //dtor
    GLCALL(glDeleteTextures(1, &m_RendererID));
    m_RendererID = 0;
    m_LocalBuffer = nullptr;
}

void Texture::Bind(unsigned int slot)
{
    m_texSlot = slot;
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}


void Texture::Bind()
{
    GLCALL(glActiveTexture(GL_TEXTURE0 + m_texSlot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{

}
