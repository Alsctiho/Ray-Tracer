#pragma once

#include <vecmath.h>

#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

#define TO_STRING( x ) #x

//****************
// COMPONENT_DECLARATION
//
// This macro must be included in the declaration of any subclass of Component.
// It declares variables used in type checking.
//****************
#define COMPONENT_DECLARATION(classname)                                                    \
public:                                                                                     \
    static const std::size_t s_type;                                                        \
    virtual bool IsClassType(const std::size_t classType) const override;

//****************
// COMPONENT_DEFINITION
// 
// This macro must be included in the class definition to properly initialize 
// variables used in type checking. Take special care to ensure that the 
// proper parentclass is indicated or the run-time type information will be
// incorrect. Only works on single-inheritance RTTI.
//****************
#define COMPONENT_DEFINITION(parentclass, childclass)                                       \
const std::size_t childclass::s_type = std::hash<std::string>()(TO_STRING(childclass));     \
bool childclass::IsClassType(const std::size_t classType) const {                           \
        if (classType == childclass::s_type)                                                \
            return true;                                                                    \
        return parentclass::IsClassType(classType);                                         \
}   

class Component
{
public:    
    virtual ~Component() = default;

    static const std::size_t s_type;
    virtual bool IsClassType(const std::size_t classType) const
    {
        return classType == Component::s_type;
    }
};