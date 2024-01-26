#include "control.hpp"
#include <vector>
#include <iostream>

using namespace std;


const char * control::endBodyName= "wrist_3_link";
vector<double>  control::endBodyPos= {0.0,0.0,0.0};



void control::mycontroller(mjModel *m, mjData *d)
{
    //get the robot independant control inputs  
    int n=m->nu;
   //  
    for (size_t i = 0; i < n; i++)
    {   // apply harmonic load 
         d->ctrl[i]=sin(d->time+i*0.5);
    }
   // mju_scl(d->ctrl, d->qvel, -0.1, m->nv);
}


void control::getState(mjModel*m,mjData*d){
    // get the number of genrisled coordinates 

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
        //
        control::endBodyPos[0]=d->xpos[3*qposadr+1];
        control::endBodyPos[1]=d->xpos[3*qposadr+2];
        control::endBodyPos[2]=d->xpos[3*qposadr+3];
    }else{
        // body not found 
        cout << "body "<< bodyName << "not found !";
       
    }
}
