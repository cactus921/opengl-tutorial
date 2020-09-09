#include "Camera.h"

Camera::Camera(glm::mat4 projectionMatrix)
    :   TransformComponent {},
        m_ProjectionMatrix (projectionMatrix)
{
    //ctor
}
Camera::Camera(Transform starterTransform, glm::mat4 projectionMatrix)
    :   TransformComponent (starterTransform),
        m_ProjectionMatrix (projectionMatrix)
{
    //ctor
}

Camera::Camera(glm::mat4 starterTransform, glm::mat4 projectionMatrix)
    :   TransformComponent (starterTransform),
        m_ProjectionMatrix (projectionMatrix)
{
    //ctor
}

Camera::~Camera()
{
    //dtor
}


void Camera::UpdateProperties()
{
    //m_ProjViewMatrix = m_ProjectionMatrix * TransformComponent.GetTransform() ;
}

/*
glm::mat4 Camera::GetProjViewMatrix()
{
    UpdateProperties();
    return m_ProjViewMatrix;
}
*/