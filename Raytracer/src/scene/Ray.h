#pragma once

#include <vecmath.h>

// A ray has a position where the ray starts, and a direction (which should
// always be normalized!)

class Ray {
public:
    Ray();

    /// <summary>
    /// construct a ray by its position and direction.
    /// </summary>
    /// <param name="pp">position</param>
    /// <param name="dd">direction</param>
    Ray(const vec3f& pp, const vec3f& dd);
    Ray(const Ray& other);
    ~Ray() {}

    Ray& operator =(const Ray& other);

    vec3f at(double t) const;

    vec3f getPosition() const;
    vec3f getDirection() const;
    vec3f getIsecPosition(double t) const;

protected:
    vec3f p;
    vec3f d;
};