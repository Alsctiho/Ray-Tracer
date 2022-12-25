#pragma once
#include <vecmath.h>

class Material
{


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

    double shininess;
    double index;               // index of refraction
};