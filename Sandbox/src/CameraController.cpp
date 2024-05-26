#pragma once

#include "CameraController.h"

#include <Input/Input.h>

using namespace yoyo;

void CameraController::AttachCamera(Ref<yoyo::Camera> camera)
{
    m_camera = camera;
}

void CameraController::Update(float dt)
{
    YASSERT(m_camera != nullptr, "Camera controller has not attached camera!");

    if(Input::GetKey(KeyCode::Key_w)) 
    {
        m_camera->position += m_camera->Front() * m_movement_speed * dt;
    }

    if(Input::GetKey(KeyCode::Key_s)) 
    {
        m_camera->position -= m_camera->Front() * m_movement_speed * dt;
    }

    if(Input::GetKey(KeyCode::Key_d)) 
    {
        m_camera->position += m_camera->Right() * m_movement_speed * dt;
    }

    if(Input::GetKey(KeyCode::Key_a)) 
    {
        m_camera->position -= m_camera->Right() * m_movement_speed * dt;
    }

    if(Input::GetKey(KeyCode::Key_Space)) 
    {
        m_camera->position += m_camera->Up() * m_movement_speed * dt;
    }

    if(Input::GetKey(KeyCode::Key_q)) 
    {
        m_camera->position -= m_camera->Up() * m_movement_speed * dt;
    }

    if(Input::GetMouseButton(MouseButton::RightMouseButton))
    {
        IVec2 mouse_position = Input::GetMousePosition();
        m_mouse_position = {(float)mouse_position.x, (float)mouse_position.y};

        if(m_just_pressed)
        {
            m_last_mouse_position = m_mouse_position;
            m_just_pressed = false;
        }

        Vec2 relative_mouse_position = {m_mouse_position  - m_last_mouse_position};
        m_camera->yaw += relative_mouse_position.x * m_mouse_sensitivity;
        m_camera->pitch += -relative_mouse_position.y * m_mouse_sensitivity;

        m_last_mouse_position = m_mouse_position;
    }
    else
    {
        m_just_pressed = true;
    }

    m_camera->UpdateCameraVectors();
}

void CameraController::SetMouseSensitivity(float sens)
{
    m_mouse_sensitivity = sens;
}

void CameraController::SetMovementSpeed(float ms)
{
    m_movement_speed = ms;
}
