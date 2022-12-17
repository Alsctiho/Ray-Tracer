#include "Application/Application.h"
#include "Layer/Layer.h"

#include <iostream>
#include <memory>

Application* Application::s_application = nullptr;

class SampleLayer : public Layer
{
private:
    float f = 0.0f;
    int counter = 0;

public:
    virtual void OnUIRender() override
    {
        // Create a window called "Hello, world!" and append into it.
        ImGui::Begin("Hello, world!");          

        // Display some text (you can use a format strings too)
        ImGui::Text("This is some useful text.");
        // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

        // Buttons return true when clicked (most widgets return true when edited/activated)
        if (ImGui::Button("Button", ImVec2(50, 20)))
            counter++;

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
};

int main()
{
    Application* app = Application::GetInstance();
    app->PushLayer(std::make_shared<SampleLayer>());
    app->Run();
}