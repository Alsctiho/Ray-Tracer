#pragma once
#include "..\Application\Logger.h"
#include "Layer.h"
#include <string>

/// <summary>
/// Reference: https://github.com/ocornut/imgui/issues/300
/// </summary>
class LogLayer : public Layer
{
private:
	ImGuiTextBuffer buffer;
	static LogLayer* s_logLayer;

public:
	LogLayer();
	void NewLine(LogLevel level, const std::string& content);
	void Append(const std::string& content);
	void EndLine();

	void OnAttach() override;
	void OnUIRender() override;
	static LogLayer* GetInstance() { return s_logLayer; }

private:
	void Clear() { buffer.clear(); }
};