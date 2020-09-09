#include "PointLight.h"

PointLight::PointLight(glm::mat4 transform, glm::vec3 color, float intensity)
    :   Light {LIGHT_TYPE::point , color, intensity},
        TransformComponent {transform}
{
    //ctor
}

PointLight::~PointLight()
{
    //dtor
}
