#pragma once

#include "..\component\Component.h"
#include <memory>

// A placeholder for components
class SceneObject
{
public:
	virtual void AddComponent(std::shared_ptr<Component> component);
};