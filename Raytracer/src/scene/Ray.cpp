#include "Ray.h"

Ray::Ray()
    : Ray(vec3f(), vec3f()) {}

Ray::Ray(const vec3f& pp, const vec3f& dd)
    : p(pp), d(dd) {}

Ray::Ray(const Ray& other)
    : p(other.p), d(other.d) {}

Ray& Ray::operator =(const Ray& other)
{
    p = other.p; d = other.d; return *this;
}

vec3f Ray::at(double t) const
{
    return p + (t * d);
}

vec3f Ray::getPosition() const { return p; }
vec3f Ray::getDirection() const { return d; }
vec3f Ray::getIsecPosition(double t) const { return p + t * d; }