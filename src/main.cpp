/**
 * @file main
 * @date 
 * 
 * 
 * 
 * 
 * 
*/

#include "mujoco/mujoco.h"
#include "mujoco/mjvisualize.h"
#include "mujoco/mjrender.h"
#include <iostream>
 
int main() {
   // create a mjrRect structure
mjrRect viewport;
 
// assign values to the fields of the structure
viewport.left = 0; // left coordinate of the viewport
viewport.bottom = 0; // bottom coordinate of the viewport
viewport.width = 800; // width of the viewport in pixels
viewport.height = 600; // height of the viewport in pixels
   mjvCamera cam;                      // abstract camera
   mjvOption opt;                      // visualization options
   mjvScene scn;                       // abstract scene
   mjrContext con;                     // custom GPU context

   std::cout <<"start";
    // Load model from file
    mjModel* m = mj_loadXML("model.xml", NULL, NULL, 0);

    // Create data structure for this model
    mjData* d = mj_makeData(m);

    // Set initial position
    d->qpos[0] = 1;

    // Run simulation for 10 seconds
    for (int t = 0; t < 1000; ++t) {
        mj_step(m, d);
      std::cout << "Step: " << t << "\n"; // Print the step index
        
        
    }
  
    mjv_defaultScene(&scn); // Set default values for the scene
    mjv_defaultCamera(&cam); // Set default values for the camera
    mjv_defaultOption(&opt); // Set default values for the options
    mjr_defaultContext(&con); // Set default values for the context
    mjr_makeContext(m, &con, 800); // Create the context with a 800-pixel buffer
    mjv_makeScene(m, &scn, 1000); // Create the scene with a 1000-object buffer
    mjv_updateScene(m, d, &opt, NULL, &cam, mjCAT_ALL, &scn); // Update the scene with the model and data
    mjr_render(viewport,  &scn, &con); // Render the scene

    // Run simulation for 10 seconds
    for (int t = 0; t < 1000; ++t) {
        mj_step(m, d); // Advance the simulation
        std::cout << "Step: " << t << "\n"; // Print the step index
        mjv_updateScene(m, d, &opt, NULL, &cam, mjCAT_ALL, &scn); // Update the scene with the new data
        mjr_render(viewport,  &scn, &con); // Render the scene
    }
    // Free memory
    mj_deleteData(d);
    mj_deleteModel(m);

    return 10;
}
