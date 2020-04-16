#include "TestTexture.h"

#include <GL/glew.h>
#include "DebugManager.h"
#include "imgui.h"



namespace test{
    TestTexture::TestTexture()
        :   m_VertPositions     {   -0.5f, -0.5f, 0.0f, 0.0f,
                                     0.5f, -0.5f, 1.0f, 0.0f,
                                     0.5f,  0.5f, 1.0f, 1.0f,
                                    -0.5f,  0.5f, 0.0f, 1.0f    },
            m_VertIndices       {   0, 1, 2,
                                    2, 3, 0     },
            m_VertexBuffer(m_VertPositions, 4 * 4 * sizeof(float)),
            m_IndexBuffer(m_VertIndices, 6),
            m_Shader("res/Basic.shader"),
            m_Texture("res/batman-logo-1.png"),
            m_MatProj           {   glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f) },
            m_MatView           {   glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) },
            m_TranslationA      {   glm::vec3(0.0f, 0.0f, 0.0f) },
            m_TranslationB      {   glm::vec3(0.0f, 0.0f, 0.0f) }
    {
        //ctor
        m_VertexLayout.Push(GL_FLOAT, 2);
        m_VertexLayout.Push(GL_FLOAT, 2);
        m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexLayout);
        m_Texture.Bind(0);
        m_Shader.Bind();
        m_Shader.SetUniform1i("u_Texture", 0);
    }

    TestTexture::~TestTexture()
    {
        //dtor
        m_Renderer.Clear();
    }

    void TestTexture::OnUpdate(float deltaTime)
    {

    }

    void TestTexture::OnRender()
    {
        m_Renderer.Clear();

        m_Shader.Bind();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_MatProj * m_MatView * model;
            m_Shader.SetUniformMat4f("u_MVP", mvp);
            m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_MatProj * m_MatView * model;
            m_Shader.SetUniformMat4f("u_MVP", mvp);
            m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
        }
    }

    void TestTexture::OnImGuiRender()
    {
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::SliderFloat3("translationA", &m_TranslationA.x, -1.0f, 1.0f);
        ImGui::SliderFloat3("translationB", &m_TranslationB.x, -1.0f, 1.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    void TestTexture::OnDestruct()
    {
        delete this;
    }

}
