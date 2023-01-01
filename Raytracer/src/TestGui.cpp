#include "app/Application.h"
#include "app/Logger.h"
#include "layer/Layer.h"
#include "layer/ViewportLayer.h"
#include "layer/ControlLayer.h"
#include "layer/LogLayer.h"
#include "fileio/Read.h"

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

namespace RayTracer
{
    Log log{ Message };
    Log error{ Error };
    Log warning{ Warning };
    Endl endl;
}

int main()
{
    Application* app = new Application(ApplicationSpecification{ "RayTracing", 1600, 900 });
    app->PushLayer(std::make_shared<DemoLayer>());
    app->PushLayer(std::make_shared<LogLayer>());
    app->PushLayer(std::make_shared<ControlLayer>());
    app->PushLayer(std::make_shared<ViewportLayer>());

    try
    {
        SceneReader reader;
        std::shared_ptr<Scene> scene = reader.ReadScene("data/sample_scene.ray");
    }
    catch (const ReadFileException& rfe)
    {
        rfe.LogMessage();
    }



    app->Run(); 
}                                                     