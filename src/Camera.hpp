#pragma once

#include <cmath>
#include <complex>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp>

template<typename T>
struct CameraConfiguration
{
	T x, y, z;
	T horizontalAngle;
	T verticalAngle;
	T fieldOfView;
	T range;
	T ratio;

	CameraConfiguration(T x=0, T y=0, T z=0, T horizontalAngle=0, 
    T verticalAngle=0, T fieldOfView=60, T range=100, T ratio=static_cast<T>(.0f/3.0f)) :
		x(x), y(y), z(z), horizontalAngle(horizontalAngle), verticalAngle(verticalAngle),
         fieldOfView(fieldOfView), range(range), ratio(ratio) {}
};


template<typename T>
class Camera
{
protected:
	~Camera() = default;
public:
	virtual glm::mat<4,4,T> getViewMatrix() const = 0;
	virtual glm::mat4 getProjectionMatrix() const = 0;
	virtual glm::vec3 getPosition() const = 0;
	virtual T getVerticalAngle() const = 0;
	virtual T getHorizontalAngle() const = 0;
	virtual T getFieldOfView() const = 0;
	virtual T getFarDepth() const = 0;

	virtual bool pointInCamera(T x, T y, T z) const = 0;
	virtual bool pointInCamera(const glm::vec3& pt) const = 0;
    virtual void move();
};