#ifdef VIEW_HPP
#define VIEW_HPP

#include"glm.hpp"

/**
 * @brief view struct : handle all openGL settings
 * @param yaw     - yaw 
 * @param pitch   - pitch 
 * @param lastX   - lastX 
 * @param lastY 
 * @param fov  
*/
struct View
{
    static float yaw   = -90.0f;	 
    static float pitch =  0.0f;
    static float lastX =  800.0f / 2.0;
    static float lastY =  600.0 / 2.0;
    static float fov   =  45.0f;
    

};
























#endif // VIEW_HPP