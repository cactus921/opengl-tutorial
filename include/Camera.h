#ifndef CAMERA_H
#define CAMERA_H
#include "Transform.h"

class Camera
{
    protected:

    private:
        void UpdateProperties();
        
        glm::mat4 m_ProjectionMatrix;
        //glm::mat4 m_ProjViewMatrix;

    public:
        Camera(glm::mat4 projectionMatrix);
        Camera(Transform transform, glm::mat4 projectionMatrix);
        Camera(glm::mat4 starterTransform, glm::mat4 projectionMatrix);
        virtual ~Camera();

        inline glm::mat4 GetProjectionMatrix() {return m_ProjectionMatrix;};

        Transform TransformComponent;
        //inline glm::mat4 GetTransform() {return m_Transform.GetTransform();};
};

#endif // CAMERA_H
