#pragma once

// The prototype/interface header for this implementation
#include "..\Layer\Layer.h"
#include "..\Layer\LogLayer.h"

// Headers from other non-standard, non-system libraries
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Headers from other "almost-standard" libraries
#include "GLFW\glfw3.h"

// Standard C++ headers
#include <memory>
#include <vector>
#include <string>
#include <iostream>

struct ApplicationSpecification
{
	std::string Name = "Application";
	uint32_t Width = 1600;
	uint32_t Height = 900;
};

class Application
{
public:
	~Application();
	void Init();
	void Run();
	void Close();

	void PushLayer(const std::shared_ptr<Layer>& layer) 
	{ 
		m_layerStack.emplace_back(layer); 
		layer->OnAttach(); 
	}

	static Application* GetInstance()
	{
		if (!s_application)
			s_application = new Application();
		return s_application;
	}

private:
	Application();
	static Application* s_application;
	std::vector<std::shared_ptr<Layer>> m_layerStack;

	// GLFW & imGUI
	ApplicationSpecification m_specification;
	GLFWwindow* window = nullptr;
	ImGuiIO* io = nullptr;
};