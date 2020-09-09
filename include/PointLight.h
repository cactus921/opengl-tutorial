#ifndef POINTLIGHT_H
#define POINTLIGHT_H
//#include "Transform.h"
#include "Light.h"
class PointLight    : public Light
{
    protected:

    private:
        Transform TransformComponent;
    public:
        PointLight(glm::mat4 transform, glm::vec3 color = glm::vec3(1.0), float intensity = 1.0);
        virtual ~PointLight();

        inline Transform* GetTransform() {return &TransformComponent;};
        virtual glm::vec3 GetDirection() {};
    
        
};

#endif // POINTLIGHT_H
