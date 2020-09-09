#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <chrono>
#include "Camera.h"
#include "Actor.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Renderer.h"

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void OnUpdate(float deltaTime);
        void OnRender();
        void OnKeyPress(int key, int action);

        void AddActor(Actor actor);
        void AddLight(Light light);
        void AddCamera(Camera camera);
        void SetClearColor(glm::vec3 color);

    protected:

    private:
        std::vector<Actor*> m_Actors;
        std::vector<Light*> m_Lights;

        Camera m_Camera;
        Renderer m_Renderer;
        glm::vec3 m_Vec3;

        bool isCameraSet = false;
        bool isLightSet = false;
        glm::mat4 defaultProjectionMatrix = 
        //std::chrono::system_clock::time_point t0;


};

#endif // SCENE_H
