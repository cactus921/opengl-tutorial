#ifndef LIGHT_H
#define LIGHT_H
//#include <glm/glm.hpp>
#include "Transform.h"

enum LIGHT_TYPE : uint {point, directional};

class Light
{
    public:
        Light(LIGHT_TYPE type, glm::vec3 color = glm::vec3(1.0), float intensity = 1.0);
        virtual ~Light();

        inline glm::vec3 GetColor() {return m_Color;};
        inline void SetColor(glm::vec3 color) {m_Color = color;};
        
        inline float GetIntensity() {return m_Intensity;};
        inline void SetIntensity(float intensity) {m_Intensity = intensity;};

        inline LIGHT_TYPE GetType() {return m_Type;};
        inline void SetType(LIGHT_TYPE type) {m_Type = type;};

        virtual Transform* GetTransform() = 0;
        virtual glm::vec3 GetDirection() = 0;
        virtual void SetDirection(glm::vec3 direction) = 0;

    protected:

    private:
        glm::vec3 m_Color;
        float m_Intensity;
        LIGHT_TYPE m_Type;
};

#endif // LIGHT_H
