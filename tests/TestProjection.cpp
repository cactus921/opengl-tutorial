#include "TestProjection.h"

#include <GL/glew.h>
#include "DebugManager.h"
#include "imgui.h"

#include "glm/gtx/euler_angles.hpp"

namespace test{

    TestProjection::TestProjection()
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
        :   m_VertPositions     {   -1.f, -1.f, -1.f,  0.25f, 0.33f, // 0
                                     1.f, -1.f, -1.f,  0.5f,  0.33f, // 1
                                     1.f,  1.f, -1.f,  0.5f,  0.66f, // 2
                                    -1.f,  1.f, -1.f,  0.25f, 0.66f, // 3

                                     1.f, -1.f, -1.f,  0.5f,  0.33f, // 1
                                     1.f, -1.f,  1.f,  0.75f, 0.33f, // 5
                                     1.f,  1.f,  1.f,  0.75f, 0.66f, // 6
                                     1.f,  1.f, -1.f,  0.5f,  0.66f, // 2

                                     1.f, -1.f,  1.f,  0.75f, 0.33f, // 5
                                    -1.f, -1.f,  1.f,  1.0f,  0.33f, // 4
                                    -1.f,  1.f,  1.f,  1.0f,  0.66f, // 7
                                     1.f,  1.f,  1.f,  0.75f, 0.66f, // 6

                                    -1.f, -1.f,  1.f,  0.0f,  0.33f, // 4
                                    -1.f, -1.f, -1.f,  0.25f, 0.33f, // 0
                                    -1.f,  1.f, -1.f,  0.25f, 0.66f, // 3
                                    -1.f,  1.f,  1.f,  0.0f,  0.66f, // 7

                                    -1.f,  1.f, -1.f,  0.25f, 0.66f, // 3
                                     1.f,  1.f, -1.f,  0.5f,  0.66f, // 2
                                     1.f,  1.f,  1.f,  0.5f,  1.0f,  // 6
                                    -1.f,  1.f,  1.f,  0.25f, 1.0f,  // 7

                                    -1.f, -1.f,  1.f,  0.25f, 0.0f, // 4
                                     1.f, -1.f,  1.f,  0.5f,  0.0f, // 5
                                     1.f, -1.f, -1.f,  0.5f,  0.33f, // 1
                                    -1.f, -1.f, -1.f,  0.25f, 0.33f    }, // 0

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
            m_Shader("res/Cube.shader"),
            m_Texture("res/rect817.png"),
            m_MatProj           {   glm::perspective(glm::radians(60.0f), 4.f/3.f, 0.1f, 100.0f) },
            //m_MatView           {   glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) },
            m_MatView           {   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)) },
            m_Translation       {   glm::vec3(0.0f, 0.0f, 0.3f) },
            m_RotationAngles    {   glm::vec3(0.0f, 0.0f, 0.0f) },
            m_Scale             {   glm::vec3(0.092f, 0.092f, 0.022f) }
    {
        //ctor
        m_VertexLayout.Push(GL_FLOAT, 3);
        m_VertexLayout.Push(GL_FLOAT, 2);
        m_VertexArray.AddBuffer(m_VertexBuffer, m_VertexLayout);
        m_Shader.Bind();
        m_Texture.Bind(0);
        m_Shader.SetUniform1i("u_Texture", 0);

        float fx = 1.00253f;
        float fy = 1.88263f;
        float cx = 0.36430f;
        float cy = 0.58882f;
        float scrsize = 0.15f;
        float width = 0.442976f * scrsize * 1.5;
        float height = 0.24917f * scrsize * 1.5;
        float znear = 0.6096f * scrsize;
        float zfar = 5.0f;

        float cx1 = cx * znear / fx;
        float cy1 = cy * znear / fy;

        glm::mat4 m;
        /*
        m[0][0] = 2.0 * fx / width;
        m[0][1] = 0.0;
        m[0][2] = 0.0;
        m[0][3] = 0.0;
        m[1][0] = 0.0;
        m[1][1] = -2.0 * fy / height;
        m[1][2] = 0.0;
        m[1][3] = 0.0;
        m[2][0] = 1.0 - 2.0 * cx / width;
        m[2][1] = 2.0 * cy / height - 1.0;
        m[2][2] = (zfar + znear) / (znear - zfar);
        m[2][3] = -1.0;
        m[3][0] = 0.0;
        m[3][1] = 0.0;
        m[3][2] = 2.0 * zfar * znear / (znear - zfar);
        m[3][3] = 0.0;
        */
        m[0][0] = 2.0 * znear / width;
        m[0][1] = 0.0;
        m[0][2] = 0.0;
        m[0][3] = 0.0;
        m[1][0] = 0.0;
        m[1][1] = 2.0 * znear / height;
        m[1][2] = 0.0;
        m[1][3] = 0.0;
        m[2][0] = -0.0 * cx1 / width;
        m[2][1] = -0.0 * cy1 / height;
        m[2][2] = (zfar + znear) / (znear - zfar);
        m[2][3] = -1.0;
        m[3][0] = 0.0;
        m[3][1] = 0.0;
        m[3][2] = 2.0 * zfar * znear / (znear - zfar);
        m[3][3] = 0.0;
        m_MatProj = m;

        //m_MatProj = GLCALL(glFrustum(-cx/2, cx/2, 0, cy, znear, zfar));
    }

    TestProjection::~TestProjection()
    {
        //dtor
        m_Renderer.Clear();
    }

    void TestProjection::OnUpdate(float deltaTime)
    {

    }

    void TestProjection::OnRender()
    {
        m_Renderer.Clear();
        GLCALL(glClearColor(0.5f, 0.7f, 1.0f, 1.0f));
        m_Shader.Bind();
        {
            glm::mat4 m_TranslationMat = glm::translate(glm::mat4(1.0f), m_Translation);
            glm::mat4 m_ScaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.092f, 0.092f, 0.022f));
            glm::mat4 Rx = glm::eulerAngleX(m_RotationAngles.x);
            glm::mat4 Ry = glm::eulerAngleY(m_RotationAngles.y);
            glm::mat4 Rz = glm::eulerAngleZ(m_RotationAngles.z);
            glm::mat4 m_OrientationMat = Rz * Ry * Rx;

            glm::mat4 model = m_TranslationMat * m_OrientationMat * m_ScaleMat;
            /*glm::mat4 model =   glm::scale(glm::rotate(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), m_Translation),
                                                                                m_RotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f)),
                                                                    m_RotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f)),
                                                        m_RotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f)),
                                            m_Scale);*/
            glm::mat4 mvp = m_MatProj * m_MatView * model;
            m_Shader.SetUniformMat4f("u_MVP", mvp);
            m_Renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
        }
    }

    void TestProjection::OnImGuiRender()
    {
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::SliderFloat3("translation", &m_Translation.x, -0.8f, 0.8f);
        ImGui::SliderFloat3("rotation", &m_RotationAngles.x, -5.0f, 5.0f);
        //ImGui::SliderFloat3("scale", &m_Scale.x, 0.1f, 5.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    void TestProjection::OnDestruct()
    {
        delete this;
    }

}
