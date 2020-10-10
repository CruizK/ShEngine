#include "OrthoCamera.h"


namespace Shengine {
OrthoCamera::OrthoCamera()
    : m_ViewMatrix(1.0f), m_Position(0), m_Transform(1.0f),
      m_Rotation(0), m_Zoom(1), m_Projection(1.0f)
{

}

OrthoCamera::~OrthoCamera()
{

}

void OrthoCamera::SetProjection(float left, float right, float bottom, float top)
{
    m_Projection = glm::ortho(left, right, bottom, top, -0.1f, 10.0f);

    m_Transform = m_Projection * m_ViewMatrix;
}

void OrthoCamera::UpdateTransform(const glm::vec2& pos, float angle, float zoom)
{
    m_Position = pos;
    m_Rotation = angle;
    m_Zoom = zoom;
    RecalcTransform();
}

void OrthoCamera::RecalcTransform()
{
    m_ViewMatrix = 
        glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0 }) *
        glm::scale(glm::mat4(1.0f), { m_Zoom, m_Zoom, 0 }) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0, 0, 1 });

    m_Transform = m_Projection * m_ViewMatrix;
}
}