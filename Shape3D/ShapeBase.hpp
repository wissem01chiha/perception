#pragma once

#include <glm/glm.hpp>

namespace ptk { 
template<typename T>
class ShapeBase
{
public:
    ShapeBase() = default;
    virtual T computeVolume() = 0;
    virtual bool intersect() = 0;
    virtual T distance() = 0;
    virtual ShapeBase affineTransform(const glm::mat<4,4,T>& tmat) = 0;
    virtual ShapeBase Scale(const T& factor) = 0;
    virtual ShapeBase Translate() = 0;
    virtual ShapeBase updateView(glm::mat<4,4,T> viewMat) = 0; 
protected:
    virtual ~ShapeBase() = 0;
};
}; // namespace ptk