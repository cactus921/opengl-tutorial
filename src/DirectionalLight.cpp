#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity)
    :   Light {LIGHT_TYPE::directional, color, intensity},
        m_Direction {direction}
{
    //ctor
}

DirectionalLight::~DirectionalLight()
{
    //dtor
}
