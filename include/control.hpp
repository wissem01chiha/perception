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
 * 
*/
struct control
{   
    static const char*         BodyName      ;
    static std::vector<double> BodyPos       ;
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
     * @brief  sets the name of the body link of a robot to get acess to getbodyPose 
     *         and other future methods 
     * @param BodyName 
     */
    void static setBodyName(const char* BodyName);
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
    *        the result is stored in endEffectorPos variable array.
    * @param m   - mujocco model object
    * @param d   - mojocco data object
    */
   static void forwardKinematics(const mjModel*m, mjData*d);

   /**
    * @brief  mpc : initate the model predictive controller of the robot 
    *         compute the control input to obtain the desired trajectory 
    * @param m  - mujocco model object
    * @param d  - mojocco data object
    * @param H 
    * @param M 
    * @param Weights 
    * @param Ts 
    * @param referenceTrajectory 
    */
   static void mpc(const mjModel*m, mjData*d, int64_t H, int64_t M,
                   std::vector<float> Weights,float Ts,
                   std::vector<float> referenceTrajectory);




};

#endif