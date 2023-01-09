#pragma once

#include "..\exception\Exception.h"
#include "..\component\Component.h"

/// <summary>
/// Ref: https://stackoverflow.com/questions/44105058/implementing-component-system-from-unity-in-c
/// </summary>
class ComponentBundle
{
public:
	/// <param name="params">Argsments for constructing the component type.</param>
	template<class ComponentType, typename... Args>
	void AddComponent(Args&&... params);

	template<class ComponentType>
	bool HasComponent();

	template<class ComponentType>
	ComponentType& GetComponent();

	template<class ComponentType>
	bool RemoveComponent();

protected:
	std::vector<std::unique_ptr<Component>> components;
};


// Note: Template must have full implementation with declaration to use.

template<class ComponentType, typename... Args>
void ComponentBundle::AddComponent(Args&&... params)
{
    // std::forward This is a helper function to allow perfect forwarding
    // of arguments taken as rvalue references to deduced types, 
    // preserving any potential move semantics involved.
    components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(params)...));
}

template<class ComponentType>
bool ComponentBundle::HasComponent()
{
    auto& index = std::find_if
    (
        components.begin(),
        components.end(),
        [classType = ComponentType::s_type](auto& component)
    {
        return component->IsClassType(classType);
    }
    );

    return index != components.end();
}

template<class ComponentType>
ComponentType& ComponentBundle::GetComponent()
{
    for (auto&& component : components)
    {
        if (component->IsClassType(ComponentType::s_type))
            return *static_cast<ComponentType*>(component.get());
    }

    throw ComponentException("dont have this component");
}

template<class ComponentType>
bool ComponentBundle::RemoveComponent()
{
    if (components.empty())
        return false;

    auto& index = std::find_if
    (
        components.begin(),
        components.end(),
        [classType = ComponentType::s_type](auto& component)
    {
        return component->IsClassType(classType);
    }
    );

    bool success = index != components.end();

    if (success)
        components.erase(index);

    return success;
}