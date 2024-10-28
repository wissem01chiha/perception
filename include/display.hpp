#pragma once

#include <opencv2/core.hpp>       
#include <opencv2/imgcodecs.hpp> 

#ifdef ENABLE_VTK
    #include <vtkActor.h>
    #include <vtkNamedColors.h>
    #include <vtkNew.h>
    #include <vtkPLYReader.h>
    #include <vtkSphereSource.h>
    #include <vtkPolyData.h>
    #include <vtkPolyDataMapper.h>
    #include <vtkProperty.h>
    #include <vtkRenderWindow.h>
    #include <vtkRenderWindowInteractor.h>
    #include <vtkRenderer.h>
    #include <vtkUnsignedCharArray.h>
    #include <vtkPointData.h>
    #include <vtkAppendPolyData.h>
    #include <vtkSmartPointer.h>
#endif

#include "camera.hpp"

//
void displayCameraPlane(){

};


void displayCorrespondence(){

};

