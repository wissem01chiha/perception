#pragma once

#include <cmath>
#include <limits>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;

namespace rpl
{
/**
 * @brief 
 * @tparam Precsion 
 */
template<class Precsion = double >
class Capsule
{
public:
    Capsule();


private:
    
};
using Capsulef = Capsule<float>;
using Capsuled = Capsule<double>;
} // namespace rpl
