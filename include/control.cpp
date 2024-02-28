//control.cpp
#include"control.hpp"
#include<iostream>
#include"mujoco/mujoco.h"
 

const char *         control::BodyName    = "wrist_3_link" ;
std::vector<double>  control::BodyPos     = {0.0,0.0,0.0}  ;
double               control::damping        = 0.4           ;
std::vector<double>  control::endEffectorPos = {0.0,0.0,0.0}  ;


void control::dampController(mjModel *m, mjData *d, double damping )
{   
    // set d->ctrl = d->qvel* scl .
    mju_scl(d->ctrl, d->qvel, damping, m->nv);
}


void control::getBodyPose(const mjModel *m, mjData * d, const char* bodyName)
{
    // get the index of the body by name
    int id= mj_name2id(m,mjOBJ_BODY, bodyName);
    // check if the body exists
    if (id >= 0 ){
        int qposadr = m->jnt_qposadr[m->body_jntadr[id]];
        // compute forward dynamics 
        mj_forward(m,d); 
        // set the body pose vector values  
        control::BodyPos[0]=d->xpos[3*qposadr+1];
        control::BodyPos[1]=d->xpos[3*qposadr+2];
        control::BodyPos[2]=d->xpos[3*qposadr+3];
    }else
    {   // body not found 
        std::cout << "body "<< bodyName << "not found !";
    }
}

void control::savePos(const mjModel* m, mjData* d , const char* posFilename){
    
}

void control::forwardKinematics(const mjModel*m, mjData*d){

control::endEffectorPos[0]=cos(d->qpos[0])*sin(d->qpos[1]+d->qpos[2]+d->qpos[3]);
control::endEffectorPos[1]=1;
control::endEffectorPos[2]=1;

}
