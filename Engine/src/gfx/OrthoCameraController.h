#pragma once
#include "OrthoCamera.h"


namespace Shengine {

class OrthoCameraController
{
public:
    OrthoCameraController(float width, float height);
    ~OrthoCameraController();

    inline const OrthoCamera& GetCamera() const { return m_Camera; }

    void Update(float dt);
private:
    OrthoCamera m_Camera;
    glm::vec2 m_Position;
    float m_Rotation;
    float m_Zoom;
};

}