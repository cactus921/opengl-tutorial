#ifndef ACTOR_H
#define ACTOR_H
#include "Transform.h"
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"
//#include "VertexBufferLayout.h"
//#include "VertexArray.h"
#include "DebugManager.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"


struct Mesh
{
    VertexBuffer vertex_buffer;
    //VertexBufferLayout vertex_layout;
    VertexArray vertex_array;
    IndexBuffer index_buffer;
};

struct Material
{
    Shader shader;
    Texture texture;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};


class Actor
{
    protected:

    private:
        
        float m_VertPositions[8 * 4 * 6];
        unsigned int m_VertIndices[6 * 6];
        Mesh m_Mesh;
        Material m_Material;
        /*
        VertexBuffer m_VertexBuffer;
        VertexArray m_VertexArray;
        IndexBuffer m_IndexBuffer;
        Shader m_Shader;
        Texture m_Texture;
        */

    public:
        Actor(glm::mat4 starterTransform, const std::string& shaderSource, const std::string& texture, unsigned int textureSlot,
                glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
        virtual ~Actor() {};

        void OnUpdate(glm::mat4 mvp);
        void BindMaterial();

        inline VertexArray& GetVA() {return m_Mesh.vertex_array;};
        inline IndexBuffer& GetIB() {return m_Mesh.index_buffer;};
        inline Shader& GetShader()  {return m_Material.shader;};

        Transform TransformComponent;
};

#endif // ACTOR_H
