#pragma once

#include "Layer.h"
#include "..\Imageio\Image.h"

#include "stb\stb_image.h"
#include "GLFW\glfw3.h"

#include <memory>

class ViewportLayer : public Layer
{
private:
    std::shared_ptr<Image> image;

public:
    virtual void OnAttach() override
    {
        image = std::make_shared<Image>("data\\Neko.jpg");
        //image = std::make_shared<Image>(600, 300, ImageFormat::RGB);
    }

    virtual void OnUIRender() override
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImVec2(image->GetWidth(), image->GetHeight()));
        ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
        ImGui::Image((void*)(intptr_t)image->GetDescriptorSet(), ImVec2(image->GetWidth(), image->GetHeight()));
        ImGui::End();
        ImGui::PopStyleVar();
    }
};