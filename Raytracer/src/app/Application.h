#pragma once

// The prototype/interface header for this implementation
#include "..\layer\Layer.h"
#include "..\layer\LogLayer.h"
#include "..\raytracer\RayTracer.h"

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
	Application(ApplicationSpecification m_specification, RayTracer* tracer);
	~Application();
	void Init();
	void Run();
	void Close();

	void SetTracerImage(Image* image)
	{
		m_tracer->SetImage(image);
	}

	void SetTracerScene(Scene* scene)
	{
		m_tracer->SetScene(scene);
	}

	void PushLayer(const std::shared_ptr<Layer>& layer) 
	{ 
		m_layerStack.emplace_back(layer); 
		layer->OnAttach(); 
	}

	static Application* GetInstance()
	{
		return s_application;
	}

	void RayTrace();

private:
	static Application* s_application;
	RayTracer* m_tracer = nullptr;
	std::vector<std::shared_ptr<Layer>> m_layerStack;

	// GLFW & imGUI
	ApplicationSpecification m_specification;
	GLFWwindow* window = nullptr;
	ImGuiIO* io = nullptr;
};