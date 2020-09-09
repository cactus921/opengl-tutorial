#include "Light.h"

Light::Light(LIGHT_TYPE type, glm::vec3 color, float intensity)
    :   m_Type{type},
        m_Color{color},
        m_Intensity{intensity}
{
    //ctor
    if (intensity > 1.0)    m_Intensity = 1.0;
    if (intensity < 0.0)    m_Intensity = 0.0;
}

Light::~Light()
{
    //dtor
}
