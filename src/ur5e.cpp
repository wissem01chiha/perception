/**
 * @file   ur5e.cpp 
 * @author wissem chiha
 * @date   Januray 2024
 * @note   this script render the robot in a static window view 
 *         with default control inputs set to 0.0
 * @ref    refer to the documentation at :  
*/
#define GLFW_DLL 
#define GLFW_INCLUDE_NONE


// cpp include
#include <iostream>

// MuJoCo include
#include "mujoco/mujoco.h"
#include "mujoco/mjvisualize.h"
#include "mujoco/mjrender.h"

// GLFW include
#include "GLFW/glfw3.h"
#include "../glm/glm.hpp"


// private include
#include"../include/global.hpp"
#include"../include/global.cpp"
#include"../include/control.hpp"
#include"../include/control.cpp"
 

//global variables
char error[1000] ;
float xscale=100.0f, yscale=100.0f;

// MuJoCo data structures
mjModel*         m;           // MuJoCo model
mjData*          d;           // MuJoCo data
mjvCamera      cam;           // abstract camera
mjvOption      opt;           // visualization options
mjvScene       scn;           // abstract scene
mjrContext     con;           // custom GPU context
mjvPerturb    pert;           // set th default perturbation 

// main loop 
int main(int argc, const char* argv[])
{   
    string filePath;
    if (argc >1)
    {   
        filePath=argv[1];
    }else
    {   cout << " no user model input folder : display from default folder"<<"\n";
        filePath =global::modelFilePath;
    }
    // load MuJoCo model 
    m = mj_loadXML(filePath.c_str(), nullptr, error, global::bufferErrorSize);
    // verify model loding correctly 
    if(m==NULL){
       cout << "model load failed !";
      
    }
    d = mj_makeData(m);
    // set initial sate position to default
    d->qpos = global::intialPosition;

    // init GLFW
    glfwInit();

    // create window, request v-sync
    GLFWwindow* window = glfwCreateWindow (global::windowLength,global::windowWidth, global::windowTitle, NULL, NULL);
    
    // set time elapsed since GLFW was initialized
    double startTime = glfwGetTime();
    

    if (glfwRawMouseMotionSupported()){ 
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
       }

    //  make OpenGL context current
    glfwMakeContextCurrent(window);
   
    // ste the openGL swap interval 
    glfwSwapInterval(global::bufferSwap);

    // initialize visualization data structures
    mjv_defaultCamera(&cam)  ;
    mjv_defaultPerturb(&pert);
    mjv_defaultOption(&opt)  ;
    mjr_defaultContext(&con) ;

    // create scene and context
    mjv_makeScene(m, &scn, global::geomtryScene);
    mjr_makeContext(m, &con, mjFONTSCALE_100);
    // create a room size and up vector
    mjtNum roomup[3] = {-5.0, 18.0, -1.0};
    //  main loop 
    while (!glfwWindowShouldClose(window)){

       
        // get GLFW time elapsed
        double glfwtime=glfwGetTime()-startTime;
        std::cout << glfwtime<< "\n";
        
        glfwGetWindowContentScale(window, &xscale, &yscale);
        mjtNum simstart = d->time;
        while (d->time - simstart <  global::simTime){
            mj_step1(m, d);
           
            control::dampController(m,d,control::damping);
            mj_step2(m, d);
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
  
    return 0;

}

