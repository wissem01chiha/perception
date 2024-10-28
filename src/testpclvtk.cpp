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

int main(int argc, char* argv[])
{
    vtkNew<vtkNamedColors> colors;

    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " Filename(.ply) e.g. shark.ply" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFilename = argv[1];

    vtkNew<vtkPLYReader> reader;
    reader->SetFileName(inputFilename.c_str());
    reader->Update();  // Ensure the reader updates its output

    vtkPolyData* polyData = reader->GetOutput();
    vtkPointData* pointData = polyData->GetPointData();

    // Ensure the color array is named "RGBA"
    vtkUnsignedCharArray* colorsArray = vtkUnsignedCharArray::SafeDownCast(pointData->GetArray("RGBA"));
    if (!colorsArray)
    {
        std::cerr << "Error: The PLY file does not contain an array named 'RGBA'!" << std::endl;
        return EXIT_FAILURE;
    }

    vtkIdType numPoints = polyData->GetNumberOfPoints();
    std::cout << "Number of points: " << numPoints << std::endl;

    vtkNew<vtkAppendPolyData> appendFilter;

for (vtkIdType i = 0; i < numPoints; ++i)
{
    double p[3];
    polyData->GetPoint(i, p);

    unsigned char* color = colorsArray->GetPointer(4 * i);
    unsigned char rgba[4] = {
        color[0], // Red
        color[1], // Green
        color[2], // Blue
        color[3]  // Alpha (transparency)
    };

    // Create a small sphere for each point
    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->SetCenter(p);
    sphereSource->SetRadius(0.01); // Small radius for each point
    sphereSource->SetThetaResolution(8);
    sphereSource->SetPhiResolution(8);
    sphereSource->Update();

    // Get the number of points in this sphere
    vtkIdType numSpherePoints = sphereSource->GetOutput()->GetNumberOfPoints();

    // Create a color array and add the color for each point in the sphere
    vtkNew<vtkUnsignedCharArray> colorArray;
    colorArray->SetNumberOfComponents(4); // RGBA has 4 components
    colorArray->SetName("Colors");

    for (vtkIdType j = 0; j < numSpherePoints; ++j)
    {
        colorArray->InsertNextTypedTuple(rgba);
    }

    // Associate the color array with the sphere's polydata
    sphereSource->GetOutput()->GetPointData()->SetScalars(colorArray);

    // Append each sphere's polydata to the append filter
    appendFilter->AddInputConnection(sphereSource->GetOutputPort());
}

    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);
 /*
    // Create and color an additional sphere
    vtkNew<vtkSphereSource> additionalSphereSource;
    additionalSphereSource->SetCenter(-34.103, -173.565, 21.563); // Position of the additional sphere
    additionalSphereSource->SetRadius(0.5); // Radius of the additional sphere
    additionalSphereSource->SetThetaResolution(20);
    additionalSphereSource->SetPhiResolution(20);
    additionalSphereSource->Update();

    vtkNew<vtkPolyDataMapper> additionalSphereMapper;
    additionalSphereMapper->SetInputConnection(additionalSphereSource->GetOutputPort());

    vtkNew<vtkActor> additionalSphereActor;
    additionalSphereActor->SetMapper(additionalSphereMapper);
    additionalSphereActor->GetProperty()->SetColor(250 ,125,1.0); // Set predefined color
    additionalSphereActor->GetProperty()->SetOpacity(1.0); // Fully opaque
 */
    // Create an actor for the combined point spheres
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(appendFilter->GetOutputPort());
     // Ensure scalar visibility is off
    mapper->ScalarVisibilityOn(); // Enable scalar visibility
mapper->SetScalarModeToUsePointData(); // Use point data for coloring
mapper->SelectColorArray("Colors");






    vtkNew<vtkActor> pointCloudActor;
    pointCloudActor->SetMapper(mapper);

    // Add the actors to the renderer
    renderer->AddActor(pointCloudActor);
    //renderer->AddActor(additionalSphereActor); // Add the additional sphere actor
    renderer->SetBackground(colors->GetColor3d("White").GetData());  // Set background color

    renderWindow->SetWindowName("Point Cloud with Additional Colored Sphere");
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
