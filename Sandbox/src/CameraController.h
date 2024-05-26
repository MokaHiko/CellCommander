#pragma once

#include <Core/Memory.h>
#include <Renderer/Camera.h>
#include <Math/Math.h>

class CameraController  
{
public:
    void AttachCamera(Ref<yoyo::Camera> camera);
    void Update(float dt);

    void SetMouseSensitivity(float sens);
    void SetMovementSpeed(float ms);
private:
    yoyo::Vec2 m_mouse_position = {0.0f, 0.0f};
    yoyo::Vec2 m_last_mouse_position = {0.0f, 0.0f};
    bool m_just_pressed = true;

    float m_movement_speed = 10.0f;
    float m_mouse_sensitivity = 0.5f;
    Ref<yoyo::Camera>  m_camera;
};