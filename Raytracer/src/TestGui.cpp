#include "app/Application.h"
#include "app/Logger.h"
#include "layer/Layer.h"
#include "layer/ViewportLayer.h"
#include "layer/ControlLayer.h"
#include "layer/LogLayer.h"
#include "fileio/Read.h"
#include "raytracer/RayTracer.h"

#include <iostream>
#include <memory>

class DemoLayer : public Layer
{
public:
    virtual void OnUIRender() override
    {
        ImGui::ShowDemoWindow();
    }
};

Application* Application::s_application = nullptr;
LogLayer* LogLayer::s_logLayer = nullptr;

namespace Skadi
{
    Log log{ Message };
    Log error{ Error };
    Log warning{ Warning };
    Endl endl;
}

int main()
{
    RayTracer* tracer = new RayTracer();
    Application* app = new Application(ApplicationSpecification{ "RayTracing", 1600, 900 }, tracer);
    //app->PushLayer(std::make_shared<DemoLayer>());
    app->PushLayer(std::make_shared<LogLayer>());
    app->PushLayer(std::make_shared<ControlLayer>());
    app->PushLayer(std::make_shared<ViewportLayer>());

    // TODO
    SceneReader reader;
    std::shared_ptr<Scene> scene = reader.ReadScene("data/sample_scene.ray");
    tracer->SetScene(scene.get());

    app->Run();

    delete app;
}