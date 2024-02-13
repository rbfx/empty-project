// Copyright (c) 2023-2023 the rbfx project.
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT> or the accompanying LICENSE file.

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>

#include <Core.SamplePlugin/SampleComponent.h>

using namespace Urho3D;

class MyApplication : public Application
{
    // Enable type information.
    URHO3D_OBJECT(MyApplication, Application);

public:
    /// Construct.
    explicit MyApplication(Context* context);

    /// Setup before engine initialization. Modifies the engine parameters.
    void Setup() override;
    /// Setup after engine initialization. Creates the logo, console & debug HUD.
    void Start() override;
    /// Cleanup after the main loop. Called by Application.
    void Stop() override;

private:
    /// Update event handler.
    void Update(VariantMap& eventData);

    /// Scene to be rendered.
    SharedPtr<Scene> scene_;
    /// Viewport that renders the scene.
    SharedPtr<Viewport> viewport_;

    /// Geometry in the scene.
    WeakPtr<Node> geometryNode_;
};

// Define entry point.
URHO3D_DEFINE_APPLICATION_MAIN(MyApplication);

MyApplication::MyApplication(Context *context)
    : Application(context)
{
}

void MyApplication::Setup()
{
    // Organization and application names are used to create writeable folder in OS-specific location.
    // For example, on Windows it would be C:/Users/<username>/AppData/Roaming/<orgname>/<appname>
    engineParameters_[EP_ORGANIZATION_NAME] = "My Organization";
    engineParameters_[EP_APPLICATION_NAME] = "My Application";
    // conf:// directory is mapped to that writeable folder.
    engineParameters_[EP_LOG_NAME] = "conf://MyApplication.log";
}

void MyApplication::Start()
{
    SampleComponent::RegisterObject(context_);

    auto cache = GetSubsystem<ResourceCache>();
    auto renderer = GetSubsystem<Renderer>();

    // Create scene.
    scene_ = MakeShared<Scene>(context_);
    scene_->CreateComponent<Octree>();

    // Create camera.
    Node* cameraNode = scene_->CreateChild("Camera");
    Camera* camera = cameraNode->CreateComponent<Camera>();

    // Create zone.
    Zone* zone = scene_->CreateComponent<Zone>();
    zone->SetFogColor(0xC9C0BB_rgb);

    // Create box geometry.
    geometryNode_ = scene_->CreateChild("Box");
    geometryNode_->SetPosition(Vector3{0.0f, 0.0f, 5.0f});
    geometryNode_->SetRotation(Quaternion{-30.0f, 60.0f, 50.0f});
    StaticModel* geometry = geometryNode_->CreateComponent<StaticModel>();
    geometry->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    geometry->SetMaterial(cache->GetResource<Material>("Materials/DefaultGrey.xml"));
    SampleComponent* sampleComponent = geometryNode_->CreateComponent<SampleComponent>();
    sampleComponent->SetAxis(Vector3::UP);
    sampleComponent->SetRotationSpeed(10.0f);

    // Create light.
    Node* lightNode = scene_->CreateChild("Light");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);

    // Create viewport.
    const auto viewport = MakeShared<Viewport>(context_, scene_, camera);
    renderer->SetViewport(0, viewport);

    SubscribeToEvent(E_UPDATE, &MyApplication::Update);
}

void MyApplication::Stop()
{

}

void MyApplication::Update(VariantMap& eventData)
{
    auto input = GetSubsystem<Input>();
    if (input->GetKeyPress(KEY_ESCAPE))
        SendEvent(E_EXITREQUESTED);
}
