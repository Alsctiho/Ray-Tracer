#include "LogLayer.h"
#include "..\app\Application.h"
#include <string>
#include <iostream>

LogLayer::LogLayer() { s_logLayer = this; }

void LogLayer::NewLine(LogLevel level, const std::string& content)
{
	switch (level)
	{
	case Warning:
		buffer.append("[Warning] ");
		break;
	case Error:
		buffer.append("  [Error] ");
		break;
	case Message:
		buffer.append("   [Text] ");
		break;
	}
	buffer.append(content.c_str());
}

void LogLayer::Append(const std::string& content)
{
	buffer.append(content.c_str());
}

void LogLayer::EndLine()
{
	buffer.append("\n");
}

void LogLayer::OnAttach()
{
	
}

void LogLayer::OnUIRender()
{
	ImGui::SetNextWindowSize(ImVec2(500, 400));
	ImGui::Begin("Console");
	if (ImGui::Button("Clear")) Clear();
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	// TODO: filter
	ImGui::Separator();
	ImGui::BeginChild("scrolling");
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
	if (copy) ImGui::LogToClipboard();
	ImGui::TextUnformatted(buffer.begin());
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::End();
}