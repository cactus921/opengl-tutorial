#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

enum ENT_AXIS{X, Y, Z};


/*******************
Base Class for all entities that exist in the world.
This class handles transforms.
*******************/
class Transform
{
    protected:
        glm::mat4 m_Transform;


    private:
        void UpdateProperties();
        //float Tx, Ty, Tz, Rx, Ry, Rz, Sx, Sy, Sz;
        glm::vec3 m_Translation, m_Scale, m_RotationAngles, m_Skew;
        glm::quat m_Orientation;
        glm::vec4 m_Perspective;


    public:
        //Transform();
        Transform(glm::mat4 starterTransform = glm::mat4(1.0));
        //Transform(glm::vec3 starterPosition);
        //Transform(glm::vec3 starterTranslation, glm::mat3 starterRotation);
        virtual ~Transform() {};

        virtual void OnUpdate() {};

        void SetTransform(glm::mat4 transform);
        void SetTranslation(glm::vec3 translation);
        void SetRotation(glm::quat rotation) {};

        //TODO: general translation.
        void Translate(glm::vec3 deltaT);
        void TranslateAlongAxis(ENT_AXIS axis, float delta);
        void Rotate(float angle, glm::vec3 axis);
        void RotateAroundAxis(float angle, ENT_AXIS axis);

        inline glm::mat4 GetTransform() {return m_Transform;};
        //inline glm::vec3 GetTranslation() {return glm::vec3(m_Transform[3]);};
        inline glm::vec3 GetTranslation() {return m_Translation;};
        inline glm::vec3 GetScale() {return m_Scale;};
        inline glm::vec3 GetRotationAngles() {return glm::eulerAngles(m_Orientation);};

        //glm::mat3 GetRotation(glm::mat3 rotation);




};


#endif // TRANSFORM_H_INCLUDED
