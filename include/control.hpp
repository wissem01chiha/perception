#ifndef CONTROL_HPP
#define CONTROL_HPP

#include"mujoco/mujoco.h"
#include<vector>
 

/**
 * @brief control struct handler for th robot 
 * @param endBodyName      - specify end effector body name in the model file
 * @param endBodyPos       - specify end effector body cartesian position respect 
 *                           to  the global frame.
 * @param damping          - damping factor parameter
 * @param endEffectorPos   - position of the robot end-effector
*/
struct control
{   
    static const char*         endBodyName   ;
    static std::vector<double> endBodyPos    ;
    static double              damping       ;
    static std::vector<double> endEffectorPos;
  
    
    /**
     * @brief simple controller apply damping for each dof of the robot 
     * @param m        - mujocco model object 
     * @param d        - mojocco data object
     * @param damping  - damping factor 
     */
    static void dampController(mjModel* m, mjData* d, double damping);

    /**
     * @brief compute the cartesian position of the end body of the model- 
     *        result will be stord in control : : endBodyPos 
     * @param m         - mujocco model object 
     * @param d         - mojocco data object 
     * @param bodyName  - name of the target model body 
    */
    static void getBodyPose(const mjModel* m, mjData *d , const char* bodyName);
    /**
     * @brief saves the position of a body in cartesian coordinates to a csv file format.
     * @param m           - mujocco model object
     * @param d           - mojocco data object
     * @param posFilename - name of the positions file 
     */
    static void savePos(const mjModel* m, mjData* d , const char* posFilename);

   /**
    * @brief return the x , y and z position of the robot end effector 
    * @param m   - mujocco model object
    * @param d   - mojocco data object
    */
   static void forwardKinematics(const mjModel*m, mjData*d);




};

#endif