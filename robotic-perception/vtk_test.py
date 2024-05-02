import vtk
import random

def read_off(file_path):
    points = []
    with open(file_path, 'r') as f:
        lines = f.readlines()
        if lines[0].strip() != 'OFF':
            print("Invalid OFF file")
            return None
        num_points = int(lines[1].split()[0])
        for line in lines[2:2+num_points]:
            coords = line.strip().split()
            points.append([float(coords[0]), float(coords[1]), float(coords[2])])
    return points

def main():
    filename = 'C:/Users/chiha/OneDrive/Documents/robotics-perception/robotic-perception/test4.off'
    points = read_off(filename)

    # Create VTK points
    vtk_points = vtk.vtkPoints()
    for point in points:
        vtk_points.InsertNextPoint(point)
        
    # Create a polydata object
    polydata = vtk.vtkPolyData()
    polydata.SetPoints(vtk_points)

    # Visualize the points as vertices
    vertexGlyph = vtk.vtkVertexGlyphFilter()
    vertexGlyph.SetInputData(polydata)
    vertexGlyph.Update()

    # Create a mapper and actor for the points
    point_mapper = vtk.vtkPolyDataMapper()
    point_mapper.SetInputData(vertexGlyph.GetOutput())

    point_actor = vtk.vtkActor()
    point_actor.SetMapper(point_mapper)
    point_actor.GetProperty().SetPointSize(1)  # Adjust point size as needed
    r, g, b = random.random(), random.random(), random.random()
    point_actor.GetProperty().SetColor(r, g, b)  # Red color
    

    # Create a renderer and render window
    renderer = vtk.vtkRenderer()
    render_window = vtk.vtkRenderWindow()
    render_window.AddRenderer(renderer)

    # Create a render window interactor
    render_window_interactor = vtk.vtkRenderWindowInteractor()
    render_window_interactor.SetRenderWindow(render_window)

    # Add the actor to the scene
    renderer.AddActor(point_actor)
    renderer.SetBackground(1.0, 1.0, 1.0)  # Set background color to white
    # Set camera position and focal point
    renderer.GetActiveCamera().SetPosition(0, 0, 10)
    renderer.GetActiveCamera().SetFocalPoint(0, 0, 0)
    renderer.GetActiveCamera().SetViewUp(0, 1, 0)
    renderer.ResetCamera()
    # Render and interact
    render_window.Render()
    render_window_interactor.Start()

if __name__ == "__main__":
    main()
