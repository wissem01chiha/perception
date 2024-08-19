#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/constants.hpp> 

namespace ptk {  

template<typename T>
class Line {
public:
    T u1, u2 , u3;

    Line(T& u1_, T& u2_, T& u3_ ):u1(u1_),u2(u2_),u3(u3_){};
   
    Matrix<Precision, 3, 1> toEigenVector() const{
        return Vector3<Precision>(u1, u2, u3);
    }
    
private:

        bool validateInput(){
        
        }
 
};
typedef Line<double> Lined;
typedef Line<float> Linef;
}; // namespace ptk
 