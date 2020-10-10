#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Shengine {
class OrthoCamera
{
public:
    OrthoCamera();
    ~OrthoCamera();

    void SetProjection(float left, float right, float bottom, float top);

    inline void SetPosition(const glm::vec2& pos) { m_Position = pos; RecalcTransform();}
    inline void SetRotation(float angle) { m_Rotation = angle; RecalcTransform(); }
    inline void SetZoom(float zoom) { m_Zoom = zoom; RecalcTransform(); }

    inline const glm::mat4& GetTransform() const { return m_Transform; } 


    void UpdateTransform(const glm::vec2& pos, float angle, float zoom);
private:
    void RecalcTransform();

    float m_Rotation;
    float m_Zoom;
    glm::vec2 m_Position;
    glm::mat4 m_Transform;
    glm::mat4 m_Projection;
    glm::mat4 m_ViewMatrix;
};
}