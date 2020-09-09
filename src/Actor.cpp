#include "Actor.h"

Actor::Actor(glm::mat4 starterTransform, const std::string& shaderSource, const std::string& texture, unsigned int textureSlot,
                glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    :   TransformComponent {starterTransform},

        m_VertPositions     {   -1.f, -1.f, -1.f,  0.0f, 0.0f, -1.0f,  0.25f, 0.33f, // 0
                                     1.f, -1.f, -1.f,  0.0f, 0.0f, -1.0f,  0.5f,  0.33f, // 1
                                     1.f,  1.f, -1.f,  0.0f, 0.0f, -1.0f,  0.5f,  0.66f, // 2
                                    -1.f,  1.f, -1.f,  0.0f, 0.0f, -1.0f,  0.25f, 0.66f, // 3

                                     1.f, -1.f, -1.f,  1.0f, 0.0f, 0.0f,  0.5f,  0.33f, // 1
                                     1.f, -1.f,  1.f,  1.0f, 0.0f, 0.0f,  0.75f, 0.33f, // 5
                                     1.f,  1.f,  1.f,  1.0f, 0.0f, 0.0f,  0.75f, 0.66f, // 6
                                     1.f,  1.f, -1.f,  1.0f, 0.0f, 0.0f,  0.5f,  0.66f, // 2

                                     1.f, -1.f,  1.f,  0.0f, 0.0f, 1.0f,  0.75f, 0.33f, // 5
                                    -1.f, -1.f,  1.f,  0.0f, 0.0f, 1.0f,  1.0f,  0.33f, // 4
                                    -1.f,  1.f,  1.f,  0.0f, 0.0f, 1.0f,  1.0f,  0.66f, // 7
                                     1.f,  1.f,  1.f,  0.0f, 0.0f, 1.0f,  0.75f, 0.66f, // 6

                                    -1.f, -1.f,  1.f,  -1.0f, 0.0f, 0.0f,  0.0f,  0.33f, // 4
                                    -1.f, -1.f, -1.f,  -1.0f, 0.0f, 0.0f,  0.25f, 0.33f, // 0
                                    -1.f,  1.f, -1.f,  -1.0f, 0.0f, 0.0f,  0.25f, 0.66f, // 3
                                    -1.f,  1.f,  1.f,  -1.0f, 0.0f, 0.0f,  0.0f,  0.66f, // 7

                                    -1.f,  1.f, -1.f,  0.0f, 1.0f, 0.0f,  0.25f, 0.66f, // 3
                                     1.f,  1.f, -1.f,  0.0f, 1.0f, 0.0f,  0.5f,  0.66f, // 2
                                     1.f,  1.f,  1.f,  0.0f, 1.0f, 0.0f,  0.5f,  1.0f,  // 6
                                    -1.f,  1.f,  1.f,  0.0f, 1.0f, 0.0f,  0.25f, 1.0f,  // 7

                                    -1.f, -1.f,  1.f,  0.0f, -1.0f, 0.0f,  0.25f, 0.0f, // 4
                                     1.f, -1.f,  1.f,  0.0f, -1.0f, 0.0f,  0.5f,  0.0f, // 5
                                     1.f, -1.f, -1.f,  0.0f, -1.0f, 0.0f,  0.5f,  0.33f, // 1
                                    -1.f, -1.f, -1.f,  0.0f, -1.0f, 0.0f,  0.25f, 0.33f    }, // 0

            m_VertIndices       {   0, 1, 2,
                                    2, 3, 0,
                                    4, 5, 6,
                                    6, 7, 4,
                                    8, 9, 10,
                                    10, 11, 8,
                                    12, 13, 14,
                                    14, 15, 12,
                                    16, 17, 18,
                                    18, 19, 16,
                                    20, 21, 22,
                                    22, 23, 20     },
        m_Mesh {    {m_VertPositions, sizeof(m_VertPositions)},
                    {},
                    {m_VertIndices, (int)(sizeof(m_VertIndices)/sizeof(*m_VertIndices))}    },

        m_Material {    {shaderSource},
                        {texture},
                        {ambient}, {diffuse}, {specular}, shininess }
        //m_VertexArray {},
        //m_IndexBuffer {m_VertIndices, (int)(sizeof(m_VertIndices)/sizeof(*m_VertIndices))},
        //m_VertexBuffer {m_VertPositions, sizeof(m_VertPositions)},
        //m_Shader {shaderSource}

{
    //ctor
    VertexBufferLayout vbl;
    vbl.Push(GL_FLOAT, 3);
    vbl.Push(GL_FLOAT, 3);
    vbl.Push(GL_FLOAT, 2);
    m_Mesh.vertex_array.AddBuffer(m_Mesh.vertex_buffer, vbl);

    m_Material.texture.Bind(textureSlot);
    m_Material.shader.SetUniform1i("u_Texture", textureSlot);

    GLDebugOut("Created Actor!", 0);
}

/*
Actor::~Actor()
{
    //dtor
}
*/
void Actor::OnUpdate(glm::mat4 mvp)
{
    m_Material.shader.Bind();
    m_Material.texture.Bind();
    m_Material.shader.SetUniformMat4f("u_MVP", mvp);
}

void Actor::BindMaterial()
{
    m_Material.shader.Bind();
    m_Material.texture.Bind();
    m_Material.shader.SetUniform3f("u_Material.ambient", m_Material.ambient.r, m_Material.ambient.g, m_Material.ambient.b);
    m_Material.shader.SetUniform3f("u_Material.diffuse", m_Material.diffuse.r, m_Material.diffuse.g, m_Material.diffuse.b);
    m_Material.shader.SetUniform3f("u_Material.specular", m_Material.specular.r, m_Material.specular.g, m_Material.specular.b);
    m_Material.shader.SetUniform1f("u_Material.shininess", m_Material.shininess);
}
