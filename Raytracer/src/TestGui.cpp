#include "Application/Application.h"
#include "Layer/Layer.h"
#include "Layer/ViewportLayer.h"
#include "Layer/ControlLayer.h"
#include "Layer/LogLayer.h"
#include "Application/Logger.h"

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

namespace Alice
{
    Log log{ Message };
    Log error{ Error };
    Log warning{ Warning };
    Endl endl;
}

int main()
{
    Application* app = Application::GetInstance();
    app->PushLayer(std::make_shared<DemoLayer>());
    app->PushLayer(std::make_shared<LogLayer>());
    app->PushLayer(std::make_shared<ControlLayer>());
    app->PushLayer(std::make_shared<ViewportLayer>());
    app->Run();
}