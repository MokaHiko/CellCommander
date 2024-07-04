#include "Sandbox.h"

#include <Yoyo.h>

#include <Core/Log.h>

#include <Math/Math.h>
#include <Math/MatrixTransform.h>
#include <Math/Quaternion.h>
#include <Math/Random.h>

#include <Input/Input.h>

#include <Core/Memory.h>
#include <Resource/ResourceManager.h>

#include <Renderer/RendererLayer.h>
#include <Renderer/Texture.h>
#include <Renderer/Shader.h>
#include <Renderer/Material.h>
#include <Renderer/Camera.h>
#include <Renderer/Light.h>

#include <Renderer/Model.h>
#include <Renderer/Mesh.h>

SandboxLayer::SandboxLayer(yoyo::Application *app)
    : m_app(app), m_renderer_layer(nullptr) {}

SandboxLayer::~SandboxLayer() {}

void SandboxLayer::OnAttach() {}

void SandboxLayer::OnDetatch() {}

void SandboxLayer::OnEnable()
{
    using namespace yoyo;

    YASSERT(m_app != nullptr, "Invalid application handle!");
    m_renderer_layer = m_app->FindLayer<RendererLayer>();

    // Load assets
    Ref<Shader> default_lit = ResourceManager::Instance().Load<Shader>("lit_shader");
    Ref<Shader> default_lit_instanced = ResourceManager::Instance().Load<Shader>("lit_instanced_shader");

    Ref<Material> default_material = Material::Create(default_lit, "default_material");
    Ref<Texture> default_texture = ResourceManager::Instance().Load<Texture>("assets/textures/white.yo");
    default_material->SetTexture(MaterialTextureType::MainTexture, default_texture);
    default_material->SetVec4("diffuse_color", Vec4{1.0f, 1.0f, 1.0f, 1.0f});
    default_material->SetVec4("specular_color", Vec4{1.0, 1.0f, 1.0f, 1.0f});
    default_material->SetColor(Vec4{1.0f, 1.0f, 1.0f, 1.0f});

    Ref<StaticMesh> cube_mesh = StaticMesh::Create("cube");
    cube_mesh->GetVertices() = {
        // Front face
        {Vec3(-1.0f, 1.0f, 1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f)},  // 0
        {Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f)},   // 1
        {Vec3(1.0f, -1.0f, 1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)},  // 2
        {Vec3(-1.0f, -1.0f, 1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)}, // 3

        // Back face
        {Vec3(-1.0f, 1.0f, -1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)},  // 4
        {Vec3(1.0f, 1.0f, -1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec2(0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)},   // 5
        {Vec3(1.0f, -1.0f, -1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec2(0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f)},  // 6
        {Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec2(1.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f)}, // 7

        // Top face
        {Vec3(-1.0f, 1.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec2(0.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)}, // 8
        {Vec3(1.0f, 1.0f, -1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)},  // 9
        {Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec2(1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f)},   // 10
        {Vec3(-1.0f, 1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec2(0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f)},  // 11

        // Bottom face
        {Vec3(-1.0f, -1.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec2(0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)}, // 12
        {Vec3(1.0f, -1.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)},  // 13
        {Vec3(1.0f, -1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec2(1.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f)},   // 14
        {Vec3(-1.0f, -1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec2(0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f)},  // 15

        // Left face
        {Vec3(-1.0f, 1.0f, -1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f)},  // 16
        {Vec3(-1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec2(1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f)},   // 17
        {Vec3(-1.0f, -1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)},  // 18
        {Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec2(0.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f)}, // 19

        // Right face
        {Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)},   // 20
        {Vec3(1.0f, 1.0f, -1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f)},  // 21
        {Vec3(1.0f, -1.0f, -1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec2(1.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f)}, // 22
        {Vec3(1.0f, -1.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec2(0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f)}   // 23
    };
    cube_mesh->GetIndices() = {
        // Front face
        0, 1, 2, 0, 2, 3,

        // Back face
        4, 6, 5, 4, 7, 6,

        // Top face
        8, 9, 10, 8, 10, 11,

        // Bottom face
        12, 14, 13, 12, 15, 14,

        // Left face
        16, 18, 17, 16, 19, 18,

        // Right face
        20, 22, 21, 20, 23, 22};

    // Camera
    Ref<yoyo::Camera> camera = CreateRef<yoyo::Camera>();
    camera->position = {0.0f, 0.0f, 10.0f};
    camera->UpdateCameraVectors();

    // Camera Controller
    m_camera_controller.AttachCamera(camera);
    m_camera_controller.SetMovementSpeed(10.0f);
    m_camera_controller.SetMouseSensitivity(0.5f);

    // Lights
    Ref<yoyo::DirectionalLight> dir_light = CreateRef<yoyo::DirectionalLight>();
    dir_light->color = {1.0f, 1.0f, 1.0f, 1.0f};
    dir_light->direction = yoyo::Vec4{1.0f, 1.0f, 1.0f, 1.0f} * -1.0f;

    // Scene objects
    Ref<yoyo::MeshPassObject> cube = CreateRef<yoyo::MeshPassObject>();
    cube->mesh = cube_mesh;
    cube->material = yoyo::ResourceManager::Instance().Load<yoyo::Material>("default_material");
    cube->model_matrix = {};

    // Send render packet to renderer
    yoyo::RenderPacket *rp = YNEW yoyo::RenderPacket();
    rp->new_camera = camera;
    rp->new_dir_lights.push_back(dir_light);
    rp->new_objects.push_back(cube);

    SendRenderPacket(rp);
}

void SandboxLayer::OnDisable()
{
    m_renderer_layer = nullptr;
};

void SandboxLayer::OnUpdate(float dt)
{
    m_camera_controller.Update(dt);
}

void SandboxLayer::SendRenderPacket(yoyo::RenderPacket *rp)
{
    m_renderer_layer->SendRenderPacket(rp);
}

class Sandbox : public yoyo::Application
{
public:
    Sandbox()
        : yoyo::Application({"Sandbox", 0, 0, 1920, 1080})
    {
        PushLayer(YNEW SandboxLayer(this));
    }

    ~Sandbox() {}
};

yoyo::Application *CreateApplication()
{
    return YNEW Sandbox;
};