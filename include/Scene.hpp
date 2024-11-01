#pragma once

#include <vector>
#include "Camera.hpp"

// defines a scene object as multiple N cameras in 3d space with specif poistions 
// define interation between them motion ...
template <typename T, typename CameraType, size_t n>
class Scene {
public:
    // default constructor 
    Scene();

    void setCamera(const CameraType<T>& cam);
    
    // 
    void render();

    // 
    void reconstruct();

private:
    CameraType<T> camera;
};