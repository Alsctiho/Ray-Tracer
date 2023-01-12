#pragma once

#include "Component.h"
#include <vecmath.h>

class Material : public Component
{
public:
    /*
    *   k* is the efficiency of the * material,
    *   to get the intensity of this surface point,
    *   I(R) = I(aR) * k(aR) * C(dR)
    */
    vec3f ke;                    // emissive
    vec3f ka;                    // ambient
    vec3f ks;                    // specular
    vec3f kd;                    // diffuse
    vec3f kr;                    // reflective
    vec3f kt;                    // transmissive

    double shininess = 0.0;
    double index = 1.0;               // index of refraction

    Material();

    COMPONENT_DECLARATION(Material)
};