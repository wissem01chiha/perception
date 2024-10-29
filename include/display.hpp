#pragma once

#include "user_config.h"

#include <opencv2/core.hpp>       
#include <opencv2/imgcodecs.hpp> 

#include "camera.hpp"

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

// display the carmera postions estimated from view frames 
// in 3d space each pose with a pyrimide with axis as same 
// as camera focal axis 
void displayCamera3DPose(){

};


//
void displayCameraPlane(){

};

// 
void display2DCorrespondence(){

};

// def display_region(org_image: np.ndarray,
//                    shadow_clear_image: np.ndarray,
//                    label: int,
//                    label_region: np.ndarray,
//                    contours: tuple) -> None:
//     # For debugging, cut the current shadow region from the image
//     reverse_mask = cv.cvtColor(cv.bitwise_not(label_region), cv.COLOR_GRAY2BGR)
//     img_w_hole = org_image & reverse_mask

//     temp_filter = cv.cvtColor(label_region, cv.COLOR_GRAY2BGR)
//     cv.drawContours(temp_filter, contours, -1, (255, 0, 0), 3)

//     fig, axes = plt.subplots(2, 2)

//     ax = axes.ravel()

//     plt.title(f"Shadow Region {label}")

//     ax[0].imshow(cv.cvtColor(org_image, cv.COLOR_BGR2RGB))
//     ax[0].set_title("Original Image")

//     ax[1].imshow(cv.cvtColor(temp_filter, cv.COLOR_BGR2RGB))
//     ax[1].set_title("Shadow Region")

//     ax[2].imshow(cv.cvtColor(img_w_hole, cv.COLOR_BGR2RGB))
//     ax[2].set_title("Shadow Region Cut")

//     ax[3].imshow(cv.cvtColor(shadow_clear_image, cv.COLOR_BGR2RGB))
//     ax[3].set_title("Corrected Image")

//     plt.tight_layout()
//     plt.show()
