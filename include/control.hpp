#ifndef CONTROL_HPP
#define CONTROL_HPP

#include"mujoco/mujoco.h"
using namespace std;

/**
 * @brief control struct 
 * @param endBodyName      - specify end effector body name in the model file
 * @param endBodyPos       - specify end effector body cartesian position respect 
 *                          to  the global frame.
*/
struct control
{   
    static const char*    endBodyName   ;
    static vector<double> endBodyPos    ;
  
    
    /**
     * @brief custom user controller 
     * @param m 
     * @param d 
    */
    static void mycontroller(mjModel* m, mjData* d);

    /**
     * @brief rteun the state vector of the robot defined by
    */
   static void getState(mjModel*m, mjData*d);


    /**
     * @brief compute the cartesian position of the end body of the model- 
     *        result will be stord in control : : endBodyPos 
     * @param m         - mujocco model object 
     * @param d         - mojocco data object 
     * @param bodyName  - name of the target model body 
    */
    static void getBodyPose(const mjModel* m, mjData *d , const char* bodyName);
};






#endif