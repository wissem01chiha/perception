#pragma once
#define PTK_DEVICE_FUN __host__ __device__

#include <cmath>
#include <complex>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>

#include "Point.hpp"

namespace ptk {

template<typename T>
class Box2 {
public:
    /** @brief Default constructor */
    Box2(): length(T(0)), width(T(0)){};

    /** @brief Parameterized constructor with dimensions */
    Box2(T l_, T w_): length(l_), width(w_),center(Point2<T>()) {};

    /** @brief Constructor using minimum and maximum points */
    Box2(Point2<T> minPoint_, Point2<T> maxPoint_){
        length = maxPoint_.x - minPoint_.x;
        width = maxPoint_.y - minPoint_.y;
    };

    /** @brief Constructor using coordinates of two opposite corners */
    Box2(T x1_, T y1_, T x2_, T y2_):minPoint(x1_,y1_), maxPoint(x2_,y2_){
        length = x2_ - x1_;
        width = y2_ - y1_;
    };

    /** @brief Method to compute the volume (for 2D, it's area). */
    PTK_DEVICE_FUN  inline T computeVolume(){
       return static_cast<T>(length * width) 
    };

    /** @brief Compute distance between 2 boxes centers  */
    PTK_DEVICE_FUN inline T DistanceBoxesCenter(const Box2<T>& other){
        return center.distanceTo(other.center);
    };

    /** @brief Compute distance between 2 aligned boxes */
    PTK_DEVICE_FUN DistanceAlignedBoxes(const Box2<T>& other){

    };

    /** @brief Compute distance between aligned box and oriented box.*/
    PTK_DEVICE_FUN 	DistanceAlignedBoxOrientedBox(const Box2<T>& other){

    };

    /** @brief Check if 2 aligned boxes are in intersection or not */
    PTK_DEVICE_FUN inline bool AlignedBoxesIntersects(const Box<T>& other) const {
        T d = distanceTo(other);
    
    };

private:
        T length, width;
        Point2<T> minPoint;
        Point2<T> maxPoint;
        Point2<T> center;
};

template<typename T>
class Box3 {
public:

    Box3(): length(0), width(0){}

private:
        T length;
        T width;
};

typedef Box2<double> Box2d;
typedef Box2<float>  Box2f;
typedef Box3<double> Box3d;
typedef Box3<float>  Box3f;
}; // namespace ptk