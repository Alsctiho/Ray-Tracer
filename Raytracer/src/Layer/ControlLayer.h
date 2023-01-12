#pragma once
#include "Layer.h"

class ControlLayer : public Layer
{
private:
    float f = 0.0f;
    int counter = 0;

public:
    virtual void OnUIRender() override
    {
        ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f));
        //ImGui::GetContentRegionAvail();

        // Create a window called "Hello, world!" and append into it.
        ImGui::Begin("Hello, world!");

        bool exit = false;
        // Menu Bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                ImGui::MenuItem("Exit", NULL, &exit);
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

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
        
        // Render Button
        if (ImGui::Button("Render", ImVec2(50, 20)))
            Application::GetInstance()->RayTrace();
        
        ImGui::End();
    }
};