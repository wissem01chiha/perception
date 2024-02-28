/**
 * 
 * @file test.cpp
 * 
 * execute   >> main  "${robot_file_path}"  
 * 
 * result in dipsplay the robot model file visulisation  
 * 
 * @author wissem chiha 
 * @date   Januray 2024 
 * @note 
*/
#define GLFW_DLL 
#define GLFW_INCLUDE_NONE
 
#include "mujoco/mujoco.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
 

 
#include "mujoco/mjvisualize.h"
#include "mujoco/mjrender.h"

#include<iostream>
#include<string>
#include<typeinfo>

#include "../include/global.hpp"
#include"../include/global.cpp"
#include"../include/utils.hpp"
#include "../include/utils.cpp"
#include"../include/control.hpp"
#include"../include/control.cpp"
 
 
// MuJoCo data structures
mjModel*         m;           // MuJoCo model
mjModel*     scene;
mjData*          d;           // MuJoCo data
mjvCamera      cam;           // abstract camera
mjvOption      opt;           // visualization options
mjvScene       scn;           // abstract scene
mjrContext     con;           // custom GPU context
mjvPerturb    pert;           // set th default perturbation 

using namespace std;
//*********************GLFW *****************************

 


 
//********************************************************************************


int main(int argc, const char* argv[]){
    string filePath;
    if (argc >1)
    {   
        filePath=argv[1];
    }else
    {   cout << " no user model input folder : display from defualt folder";
        filePath =global::modelFilePath;
    }
   
    char error[1000];
    
    m = mj_loadXML(filePath.c_str(), nullptr, error, global::bufferErrorSize);
    // add a  loop to verify model loding correctly 
    if(m==NULL){
       cout << "model load failed !";
    }

    
    // print th e model to a text file 
    mj_printModel( m,  global::modelTxtfile);
    d = mj_makeData(m);
   
    
    
    // get the 
    mjtNum t= d->time; 
    // get the model genralised coordinate 
     //d->qpos;
    // genralised velocities of the robot 
    //d->qvel;
    //d->act;
    // get the robot genrelised control 
    
    // Set initial position of the robot by setting each input value to 0.0
    d->qpos = global::intialPosition;
  
    //check qpos, reset if any element is too big or nan.
    mj_checkPos(m,d);
    mj_checkVel(m,d);
    mj_checkAcc(m,d);

    // init GLFW, create window, make OpenGL context current, request v-sync
    glfwInit();
    GLFWwindow* window = glfwCreateWindow (global::windowLength, global::windowWidth, global::windowTitle, NULL, NULL);
   //if (glfwRawMouseMotionSupported()){ 
   //glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);}

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(global::bufferSwap);
    //glfwSetScrollCallback(window, scroll_callback);
    
    mjv_defaultFreeCamera(m, &cam);
    // initialize visualization data structures
    //mjv_defaultCamera(&cam);

    mjv_defaultPerturb(&pert);
    mjv_defaultOption(&opt);
    mjr_defaultContext(&con);
    // create scene and context
    mjv_makeScene(m, &scn, global::geomtryScene);
    mjr_makeContext(m, &con, mjFONTSCALE_100);
    
    // get the number of bodies of the model 
    int n=m->nbody;
    //cout << "number bodies:"; // in our ur5e robot they are 8 
    
    Data data1;
    vector<double> myArray = {1.2, 3.4, 5.6, 7.8};
    data1.array2csv(myArray, global::modelTxtfile);
      
    // run main loop, target real-time simulation and 60 fps rendering
    while (!glfwWindowShouldClose(window))
    {
       // call GLFW events callbacks
       
        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //ourShader.setMat4("projection", projection);
        mjtNum simstart = d->time;
        //rest all data poses to thoses in mjmodel xml defualt and control 
        // and forces to 0
        mj_resetData(m,d);
        //computes the forward kinmatics of the model 
        
        while (d->time - simstart <  global::simTime){  
             
            // advance simulation before external force and control are applied 
            //mj_step1(m, d);
            d->ctrl[4]=2;
            d->ctrl[3]=2;
            d->ctrl[2]=-2;
            control::dampController(m,d,control::damping);
            // integrate state
            mj_step(m, d);
            
            // get end effector cartesian position 
            control::getBodyPose(m,d,control::BodyName) ;
            cout << control::BodyPos[1] << "\n";
             
        }
        // get framebuffer viewport
        mjrRect viewport = {0, 0, 0, 0};
        glfwGetFramebufferSize(window, &viewport.width, &viewport.height);
        // update scene and render
        mjv_updateScene(m, d, &opt, NULL, &cam, mjCAT_ALL, &scn);
        mjr_render(viewport, &scn, &con);
        // swap OpenGL buffers (blocking call due to v-sync)
        glfwSwapBuffers(window);
        // process pending GUI events, call GLFW callbacks
        glfwPollEvents();
}
// close GLFW, free visualization storage
glfwTerminate();
mjv_freeScene(&scn);
mjr_freeContext(&con);
}
 