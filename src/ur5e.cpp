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

// private include
#include"../include/global.hpp"

//global variables
char error[1000] ;
bool quit = false;

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
 while (!quit){ 

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
       quit=true;
    }
    // set initial sate position to default
    d->qpos = global::intialPosition;
    // init GLFW
    glfwInit();
    // create window, request v-sync
    GLFWwindow* window = glfwCreateWindow (global::windowLength,global::windowWidth, global::windowTitle, NULL, NULL);
    //  make OpenGL context current
    glfwMakeContextCurrent(window);
    //
    glfwSwapInterval(global::bufferSwap); 

 }
    return 0;

}

