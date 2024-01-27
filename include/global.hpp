#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include<string>
using namespace std;

/**
 * @brief global c++ structure that handle global variable settings for the 
 *        simulations and main programs
 * @param initialposition   - initial position of the robot 
 * @param windowWidth       - simulation GUI window width size
 * @param windowLength      - simulation GUI window length size
 * @param bufferSwap        - set equal to 1 or 0 
 * @param bufferErrorSize   - the size of the buffer error text returned 
 * @param geomtrySceneNb    - number of geomtries displayed in a scene
 * @param windowTitle       - simulation GUI window title
 * @param simTime           - simulation duration time (seconds)
 * @param viewport          - framebuffer simulation viewport
 * @param modelFilePath     - default path of the robot model xml file   
 * @param sceneFilePath     - default path of the scene model xml file
 * @param modelTxtfile      - default path of the .txt mojoco model file
 * @param figureFilePath    - default path of figures folder
 * @param windowIconPath    - default path of openGL windows icon     
 * 
*/
struct global
{     
    static   double       intialPosition[6]  ;
    static   int          windowWidth        ;
    static   int          windowLength       ;
    static   int          bufferSwap         ;
    static   int          bufferErrorSize    ;
    static   int          geomtryScene       ;
    static   double       simTime            ;
    static   const char*  windowTitle        ;
    static   string       modelFilePath      ;
    static   string       sceneFilePath      ;
    static   const char*  modelTxtfile       ;
    static   const char*  figureFilePath     ;
    static   const char*  windowIconPath     ;
   

};

#endif 
 



