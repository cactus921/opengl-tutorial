#include "TestScene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DebugManager.h"
#include "imgui.h"




namespace test{

    TestScene::TestScene()
        :

            m_Camera    (glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
                         glm::perspective(glm::radians(60.0f), 4.f/3.f, 0.1f, 100.0f)),
            t0 {std::chrono::system_clock::now()},
            m_Vec3 {glm::vec3(-0.2, -1.0, -0.3)}
            //m_Light {glm::vec3(-0.2, -1.0, -0.3)}
            //pl (glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, 1.0f, -2.0f)))
    {
        //ctor

        m_Actors.push_back(new Actor(glm::translate(glm::mat4(1.0), glm::vec3(2.0, 2.0, 0.0)), "res/Phong2.shader", "res/rect817.png", 0,
                            glm::vec3(0.0215, 0.1745, 0.0215),
                            glm::vec3(0.07568, 0.61424, 0.07568),
                            glm::vec3(0.633, 0.727811, 0.633),
                            0.6 * 128.0));
          
        m_Actors.push_back(new Actor(glm::mat4(1.0f), "res/Phong2.shader", "res/cubemap-wr.png", 1,
                            glm::vec3(0.2125, 0.1275, 0.054),
                            glm::vec3(0.714, 0.4284, 0.18144),
                            glm::vec3(0.393548, 0.271906, 0.166721),
                            0.2 * 128.0));
          

        //m_Lights.push_back(new DirectionalLight(glm::vec3(-0.2, -1.0, -0.3)));
        m_Lights.push_back(new DirectionalLight(m_Vec3));
        //m_Lights.push_back(new PointLight(glm::translate(glm::mat4(1.0f), glm::vec3(1.2f, 1.0f, -2.0f))));
        //m_Lights.push_back(new PointLight(glm::translate(glm::mat4(1.0), glm::vec3(-2.0, -2.0, -2.0)), glm::vec3(0.8, 0.7, 0.3), 1.0));
    }

    TestScene::~TestScene()
    {
        //dtor
        m_Renderer.Clear();
    }

    void TestScene::OnUpdate(float deltaTime)
    {
        float rotationVelocity = 0.02;
        for (unsigned int i=0; i<m_Actors.size(); i++)
        {
            m_Actors[i]->TransformComponent.RotateAroundAxis(rotationVelocity, ENT_AXIS::Y);
        }
        m_Lights[0]->SetDirection(m_Vec3);
    }

    void TestScene::OnRender()
    {
        m_Renderer.Clear();
        GLCALL(glClearColor(0.1f, 0.2f, 0.3f, 1.0f));
        //GLDebugOut("Start Render", 0);
        for (unsigned int i=0; i<m_Actors.size(); i++)
        {
            Actor* currentActor = m_Actors[i];
            currentActor->BindMaterial();
            glm::mat4 mvp = m_Camera.GetProjectionMatrix() * m_Camera.TransformComponent.GetTransform() * currentActor->TransformComponent.GetTransform();
            currentActor->GetShader().SetUniformMat4f("u_MVP", mvp);
            currentActor->GetShader().SetUniformMat4f("u_Model", currentActor->TransformComponent.GetTransform());
            glm::vec3 viewPos = m_Camera.TransformComponent.GetTranslation();
            currentActor->GetShader().SetUniform3f("u_ViewPos", viewPos.x, viewPos.y, viewPos.z);
            //GLDebugOut("Draw", 0);
            for(unsigned int j=0; j<m_Lights.size(); j++)
            {
                Light* currentLight = m_Lights[j];
                switch(currentLight->GetType())
                {
                    case LIGHT_TYPE::point:
                    {
                        glm::vec3 lightPos = currentLight->GetTransform()->GetTranslation();
                        currentActor->GetShader().SetUniform3f("u_LightPos", lightPos.x, lightPos.y, lightPos.z);
                        currentActor->GetShader().SetUniform1i("u_LightType", LIGHT_TYPE::point);
                        break;
                    }
                    case LIGHT_TYPE::directional:
                    {
                        glm::vec3 lightDir = currentLight->GetDirection();
                        currentActor->GetShader().SetUniform3f("u_LightDir", lightDir.x, lightDir.y, lightDir.z);
                        currentActor->GetShader().SetUniform1i("u_LightType", LIGHT_TYPE::directional);
                        break;
                    }
                }

                glm::vec3 lightColor = currentLight->GetColor();
                currentActor->GetShader().SetUniform3f("u_LightColor", lightColor.r, lightColor.g, lightColor.b);
                m_Renderer.Draw(currentActor->GetVA(), currentActor->GetIB(), currentActor->GetShader());
            }

        }
        /*
        for (unsigned int k=0; k<m_Lights.size(); k++)
        {
            PointLight* currentLight = m_Lights[k];
            currentLight->GetShader().Bind();
            glm::mat4 mvp = m_Camera.GetProjectionMatrix() * m_Camera.TransformComponent.GetTransform() * currentLight->TransformComponent.GetTransform();
            currentLight->GetShader().SetUniformMat4f("u_MVP", mvp);
            m_Renderer.Draw(currentLight->GetVA(), currentLight->GetIB(), currentLight->GetShader());
        }
        */
    }

    void TestScene::OnImGuiRender()
    {
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        //glm::vec3 t = m_Actors[0]->TransformComponent.GetTranslation();
        //ImGui::Text("%2.2f", t.x);
        //if(ImGui::Button("->")) m_Camera.TransformComponent.TranslateAlongAxis(ENT_AXIS::X, 0.2);
        ImGui::SliderFloat3("direction", &m_Vec3.x, -5.0f, 5.0f);
        //ImGui::SliderFloat3("scale", &m_Scale.x, 0.1f, 5.0f);
        //ImGui::SliderFloat3("lightsource translation", &m_TranslationLight.x, -5.0f, 5.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    void TestScene::OnDestruct()
    {
        delete this;
    }

    void TestScene::OnKeyPress(int key, int action)
    {
        if(action == GLFW_PRESS || GLFW_REPEAT)
        {
            //GLDebugOut("Key", key);
            switch(key)
            {
                case GLFW_KEY_W:
                    m_Camera.TransformComponent.TranslateAlongAxis(ENT_AXIS::Z, -0.1f);
                    break;
                case GLFW_KEY_S:
                    m_Camera.TransformComponent.TranslateAlongAxis(ENT_AXIS::Z, 0.1f);
                    break;
                case GLFW_KEY_A:
                    m_Camera.TransformComponent.TranslateAlongAxis(ENT_AXIS::X, -0.1f);
                    break;
                case GLFW_KEY_D:
                    m_Camera.TransformComponent.TranslateAlongAxis(ENT_AXIS::X, 0.1f);
                    break;
            }
        }
    }

}
