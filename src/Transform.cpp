#include "Transform.h"

Transform::Transform(glm::mat4 starterTransform)
    :   m_Transform (starterTransform)
{
    UpdateProperties();
}

void Transform::UpdateProperties()
{
    glm::decompose(m_Transform, m_Scale, m_Orientation, m_Translation, m_Skew, m_Perspective);
}

void Transform::SetTransform(glm::mat4 transform)
{
    m_Transform = transform;
    UpdateProperties();
}

void Transform::SetTranslation(glm::vec3 translation)
{
    m_Transform[3] = glm::vec4(translation, 1);
    UpdateProperties();
}

void Transform::Translate(glm::vec3 deltaT)
{
    m_Transform = glm::translate(m_Transform, deltaT);
    UpdateProperties();
}

void Transform::TranslateAlongAxis(ENT_AXIS axis, float delta)
{
    switch(axis)
    {
        case ENT_AXIS::X :
            //m_Transform = glm::translate(m_Transform, glm::vec3(delta, 0.0, 0.0));
            Translate(glm::vec3(delta, 0.0, 0.0));
            break;
        case ENT_AXIS::Y :
            //m_Transform = glm::translate(m_Transform, glm::vec3(0.0, delta, 0.0));
            Translate(glm::vec3(0.0, delta, 0.0));
            break;
        case ENT_AXIS::Z :
            //m_Transform = glm::translate(m_Transform, glm::vec3(0.0, 0.0, delta));
            Translate(glm::vec3(0.0, 0.0, delta));
            break;
    }
    UpdateProperties();
}


void Transform::Rotate(float angle, glm::vec3 axis)
{
    m_Transform = glm::rotate(m_Transform, angle, axis);
    UpdateProperties();
}

void Transform::RotateAroundAxis(float angle, ENT_AXIS axis)
{
    switch(axis)
    {
        case ENT_AXIS::X :
            Rotate(angle, glm::vec3(1.0, 0.0, 0.0));
            break;
        case ENT_AXIS::Y :
            Rotate(angle, glm::vec3(0.0, 1.0, 0.0));
            break;
        case ENT_AXIS::Z :
            Rotate(angle, glm::vec3(0.0, 0.0, 1.0));
            break;
    }
    UpdateProperties();
}