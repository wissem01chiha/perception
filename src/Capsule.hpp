#pragma once
#define PTK_DEVICE_FUN __host__ __device__

#include <cmath>
#include <complex>
#include <stdexcept>
#include <glm/glm.hpp>

#include "Point.hpp"
#include "Line.hpp"

namespace ptk{

template<typename T>
class Capsule {   
public:

    Capsule();

private:
    
};
typedef  Capsule<float> Capsulef;
typedef  Capsule<double> Capsuled;
}; // namespace ptk
