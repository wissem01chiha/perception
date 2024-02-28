//global.cpp
#include "global.hpp"
#include<string>
using namespace std;

const char* global::windowTitle       ="Mujoco-Simulation"  ; 
string      global::modelFilePath     ="../model/scene.xml" ;
string      global::sceneFilePath     ="../model/scene.xml" ;
const char* global::modelTxtfile      ="../tmp/ur5e.txt"    ;
const char* global::windowIconPath    ="../tmp/icon.png"    ;
const char* global::figureFilePath    = "../tmp"            ;
double      global::simTime           = 0.001                ;
int         global::geomtryScene      = 1000                ;
int         global::bufferErrorSize   = 1000                ;
int         global::bufferSwap        = 1                   ;
int         global::windowLength      = 1000                ;
int         global::windowWidth       = 1200                ;
double      global::intialPosition[6] = {.0,.0,.0,.0,.0,.0} ; 