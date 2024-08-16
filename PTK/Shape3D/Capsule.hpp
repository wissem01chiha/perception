#pragma once

#include <cmath>
#include <complex>
#include <stdexcept>
#include <glm/glm.hpp>


namespace ptk{

template<typename T>
struct Capsule
{   
    // Default Constructor
    Capsule();

    
};
typedef  Capsule<float> Capsulef;
typedef  Capsule<double> Capsuled;
}; // namespace ptk
