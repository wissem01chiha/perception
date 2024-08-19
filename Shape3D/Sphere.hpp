#pragma once
#define PTK_DEVICE_FUN __host__ __device__

#include <cmath>
#include <complex>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>

#include "Point.hpp"
#include "Box.hpp"

namespace ptk {  

template<typename T>
class Sphere {
public:

    /** @brief Default constructor */
    Sphere():radius(0), center(Point3<T>(0, 0, 0)) {} 

    Sphere(T radius_):radius(radius_), center(Point3<T>(0, 0, 0)) {}

    SSphere(T radius_, const Point3<T>& pt):radius(radius_), center(pt) {};

    /** @brief Compute sphere volume */
    PTK_DEVICE_FUN inline T computeVoulme(){
        return static_cast<T>(4.0/3.0*glm::pi<T>()*std::pow(radius,3));
    };

    PTK_DEVICE_FUN inline Box2<T> computeAABB() const {
        Point3<T> minPoint(center.x-radius, center.y-radius, center.z-radius);
        Point3<T> maxPoint(center.x+radius, center.y+radius, center.z+radius);
        return Box2<T>(minPoint, maxPoint);
    };

    /** @brief Return the union of 2 spheres */
    PTK_DEVICE_FUN inline Sphere<T> operator+(const Sphere<T>& other){
        T d = distanceTo(other.center);
        if (d + other.radius <= radius) {
            return *this; 
        } else if (d + radius <= other.radius) {
            return other; 
        }else {
            T newRadius = (d+ radius + other.radius) / 2;
            Point3<T> newCenter = center+((other.center-center)*
            ((newRadius-radius)/d));
            return Sphere<T>(newRadius, newCenter);
        }
    };

    /** @brief Computes the inersection volume of 2 spheres. */
    PTK_DEVICE_FUN inline T intersectVolume(const Sphere<T>& other) const {
        if (!intersect(other)) {
            return static_cast<T>(0);
        }
        T d = distanceTo(other.center);
        T r1 = radius;
        T r2 = other.radius;
        if (d == 0 && radius == r2) {
            return computeVolume(); 
        }else{
            T vol = static_cast<T>((glm::pi<T>()*(r1+r2-d)*(r1+r2-d)*
            (d*d+2*d*r1+2*d*r2-3*(r1-r2)*(r1-r2)))/(12.0*d));
        }
        return vol;
    };

    /** @brief Compute the distance between 2 spheres */
    PTK_DEVICE_FUN inline T distanceTo(const Sphere<T>& other) const {
        T dist = center.distanceTo(other.center);
        return dist;
    };

    /** @brief Check if 2 spheres are in intersection or not */
    PTK_DEVICE_FUN inline bool intersect(const Sphere<T>& other) const {
        T d = distanceTo(other);
        if (d + other.radius <= radius){
            return true;
        }else{
            return false;
        }
    }
private:
    T radius; 
    Point3<T> center; 
};
typedef Sphere<double> Shpered;
typedef Sphere<float> Shperef;
}; // namsepace ptk