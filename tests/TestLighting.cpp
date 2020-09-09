#include "TestLighting.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DebugManager.h"
#include "imgui.h"




namespace test{

    TestLighting::TestLighting()
    /*
        :   m_VertPositions     {   -1.f, -1.f, -1.f,  0.25f, 0.33f, // 0
                                     1.f, -1.f, -1.f,  0.5f,  0.33f, // 1
                                     1.f,  1.f, -1.f,  0.5f,  0.66f, // 2
                                    -1.f,  1.f, -1.f,  0.25f, 0.66f, // 3
                                    -1.f, -1.f,  1.f,  1.0f,  0.33f, // 4
                                     1.f, -1.f,  1.f,  0.75f, 0.33f, // 5
                                     1.f,  1.f,  1.f,  0.75f, 0.66f, // 6
                                    -1.f,  1.f,  1.f,  1.0f,  0.66f    }, // 7
            m_VertIndices       {   0, 1, 2,
                                    2, 3, 0,
                                    1, 5, 6,
                                    6, 2, 1,
                                    5, 4, 7,
                                    7, 6, 4,
                                    4, 0, 3,
                                    3, 7, 4,
                                    3, 2, 6,
                                    6, 7, 3,
                                    4, 5, 1,
                                    1, 0, 4     },
    */
    /*
           7_______ 6
          /       /|
        3/______2/ |
        |       |  |
        |  4    |  |5
        |       | /
        |_______|/
        0       1

    */

        :   m_VertPositions     {   -1.f, -1.f, -1.f,  0.0f, 0.0f, -1.0f,  0.25f, 0.33f, // 0
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

            m_VertexBuffer(m_VertPositions, sizeof(m_VertPositions)),
            m_IndexBuffer(m_VertIndices, (int)(sizeof(m_VertIndices)/sizeof(*m_VertIndices))),
            m_ShaderLight("res/LightSource.shader"),
            m_ShaderObject("res/Phong.shader"),
            m_Texture("res/rect817.png"),
            m_MatProj           {   glm::perspective(glm::radians(60.0f), 4.f/3.f, 0.1f, 100.0f) },
            //m_MatView           {   glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) },
            m_MatView           {   glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)) },
            m_Translation       {   glm::vec3(0.0f, 0.0f, 0.0f) },
            m_RotationAngles    {   glm::vec3(0.0f, 0.0f, 0.0f) },
            m_Scale             {   glm::vec3(1.0f, 1.0f, 1.0f) },
            m_TranslationLight       {   glm::vec3(1.2f, 1.0f, -2.0f) },

            t0 {std::chrono::system_clock::now()}
    {
        //ctor
        m_VertexLayout.Push(GL_FLOAT, 3);
        m_VertexLayout.Push(GL_FLOAT, 3);
        m_VertexLayout.Push(GL_FLOAT, 2);
        m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexLayout);
        m_ShaderObject.Bind();
        m_Texture.Bind(0);
        m_ShaderObject.SetUniform1i("u_Texture", 0);
        m_ShaderObject.SetUniform3f("u_ViewPos", 0.0, 0.0, -5.0);

    }

    TestLighting::~TestLighting()
    {
        //dtor
        m_Renderer.Clear();
    }

    void TestLighting::OnUpdate(float deltaTime)
    {
    }

    void TestLighting::OnRender()
    {
        m_Renderer.Clear();
        GLCALL(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));

        {

            glm::mat4 model =   glm::scale(glm::translate(glm::mat4(1.0f), m_TranslationLight),  glm::vec3(0.2, 0.2, 0.2));
            glm::mat4 mvp = m_MatProj * m_MatView * model;
            m_ShaderLight.Bind();
            m_ShaderLight.SetUniformMat4f("u_MVP", mvp);
            //m_ShaderLight.SetUniformMat4f("u_Model", model);
            //std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();//.time_since_epoch().count();
            //std::chrono::duration<float, std::milli> dt = t1-t0;
            //m_ShaderObject.SetUniform1f("u_Time", dt.count());

            m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_ShaderLight);
        }

        {

            glm::mat4 model =   glm::scale(glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), m_Translation),
                                                                                m_RotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f)),
                                                                    m_RotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f)),
                                                        m_RotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f)),
                                            m_Scale);
            glm::mat4 mvp = m_MatProj * m_MatView * model;
            m_ShaderObject.Bind();
            m_ShaderObject.SetUniformMat4f("u_MVP", mvp);
            m_ShaderObject.SetUniformMat4f("u_Model", model);
            m_ShaderObject.SetUniform3f("u_LightPos", m_TranslationLight.x, m_TranslationLight.y, m_TranslationLight.z);
            glm::vec3 viewPos = glm::vec3(m_MatView[3]);
            m_ShaderObject.SetUniform3f("u_ViewPos", viewPos.x, viewPos.y, viewPos.z);
            //std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();//.time_since_epoch().count();
            //std::chrono::duration<float, std::milli> dt = t1-t0;
            //m_ShaderObject.SetUniform1f("u_Time", dt.count());

            m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_ShaderObject);
        }
    }

    void TestLighting::OnImGuiRender()
    {
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::SliderFloat3("translation", &m_Translation.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("rotation", &m_RotationAngles.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("scale", &m_Scale.x, 0.1f, 5.0f);
        ImGui::SliderFloat3("lightsource translation", &m_TranslationLight.x, -5.0f, 5.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    void TestLighting::OnDestruct()
    {
        delete this;
    }

    void TestLighting::OnKeyPress(int key, int action)
    {
        if(action == GLFW_PRESS || GLFW_REPEAT)
        {
            //GLDebugOut("Key", key);
            switch(key)
            {
                case GLFW_KEY_W:
                    m_MatView = glm::translate(m_MatView, glm::vec3(0.0f, 0.0f, -0.1f));
                    break;
                case GLFW_KEY_S:
                    m_MatView = glm::translate(m_MatView, glm::vec3(0.0f, 0.0f, 0.1f));
                    break;
                case GLFW_KEY_A:
                    m_MatView = glm::translate(m_MatView, glm::vec3(-0.1f, 0.0f, 0.0f));
                    break;
                case GLFW_KEY_D:
                    m_MatView = glm::translate(m_MatView, glm::vec3(0.1f, 0.0f, 0.0f));
                    break;
            }
        }
    }

}
