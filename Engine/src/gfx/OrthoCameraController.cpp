#include "OrthoCameraController.h"
#include "../input/Input.h"
#include "../pch.h"
#include <GLFW/glfw3.h>

namespace Shengine {

    OrthoCameraController::OrthoCameraController(float width, float height)
        : m_Position(0), m_Rotation(0.0f), m_Zoom(1.0f)
    {
        m_Camera.SetProjection(0, width, 0, height);
    }

    OrthoCameraController::~OrthoCameraController()
    {

    }

    void OrthoCameraController::Update(float dt)
    {
        if(Input::IsKeyPressed(GLFW_KEY_W))
        {
            m_Position.y -= 100.0f * dt;
        }
        if(Input::IsKeyPressed(GLFW_KEY_S))
        {
            m_Position.y += 100.0f * dt;
        }
        if(Input::IsKeyPressed(GLFW_KEY_A))
        {
            m_Position.x += 100.0f * dt;
        }
        if(Input::IsKeyPressed(GLFW_KEY_D))
        {
            m_Position.x -= 100.0f *dt;
        }

        if(Input::IsKeyPressed(GLFW_KEY_Q))
        {
            m_Rotation -= 10.0f * dt;
        }

        if(Input::IsKeyPressed(GLFW_KEY_E))
        {
            m_Rotation += 10.0f * dt; 
        }

        if(Input::IsKeyPressed(GLFW_KEY_Z))
        {
            m_Zoom += 10.0f * dt;
            m_Zoom = std::min(m_Zoom, 1.5f);
        }

        if(Input::IsKeyPressed(GLFW_KEY_X))
        {
            m_Zoom -= 10.0f * dt;
            m_Zoom = std::max(m_Zoom, 0.25f);
        }

        m_Camera.UpdateTransform(m_Position, m_Rotation, m_Zoom);
    }
}