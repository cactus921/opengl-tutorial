#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "Test.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "Actor.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <chrono>
#include <vector>

namespace test {


    class TestScene : public Test
    {
        public:
            TestScene();
            ~TestScene();

            void OnUpdate(float deltaTime);
            void OnRender();
            void OnImGuiRender();
            void OnDestruct();
            void OnKeyPress(int key, int action);

        private:

            std::vector<Actor*> m_Actors;
            std::vector<Light*> m_Lights;
            //PointLight pl;
            //Actor m_MyObject;
            Camera m_Camera;
            Renderer m_Renderer;
            glm::vec3 m_Vec3;

            std::chrono::system_clock::time_point t0;
    };


}

#endif // TESTSCENE_H
