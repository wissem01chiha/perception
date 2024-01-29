#include"control.hpp"
#include<iostream>
#include"mujoco/mujoco.h"
 

// this is the body considered as the  end-effector 
const char *         control::endBodyName = "wrist_3_link" ;
std::vector<double>  control::endBodyPos  = {0.0,0.0,0.0}  ;
double               control::damping     = 1.2            ;




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
        control::endBodyPos[0]=d->xpos[3*qposadr+1];
        control::endBodyPos[1]=d->xpos[3*qposadr+2];
        control::endBodyPos[2]=d->xpos[3*qposadr+3];
    }else
    {
        // body not found 
        cout << "body "<< bodyName << "not found !";
    }
}
