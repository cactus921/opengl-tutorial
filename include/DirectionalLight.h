#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"


class DirectionalLight : public Light
{
    public:
        DirectionalLight(glm::vec3 direction, glm::vec3 color = glm::vec3(1.0), float intensity = 1.0);
        virtual ~DirectionalLight();

        inline glm::vec3 GetDirection() {return m_Direction;};
        inline void SetDirection(glm::vec3 direction) {m_Direction = direction;};

        virtual Transform* GetTransform(){};

    protected:

    private:
        glm::vec3 m_Direction;
};

#endif // DIRECTIONALLIGHT_H
