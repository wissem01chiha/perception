"""



"""
import numpy as np 
import vtk
 
def get_line_by_2pts(x,y):
    x1 = np.array([x[0], y[0], 1]).reshape(-1, 1)
    x2 = np.array([x[1], y[1], 1]).reshape(-1, 1)
    l =  np.cross(x1,x2)
    l =l /np.sqrt(l(0)**2+l(1)**2+l(2)**2)
    return l




# Create a cone
cone = vtk.vtkConeSource()
cone.SetResolution(8)

# Create a mapper
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(cone.GetOutputPort())

# Create an actor
actor = vtk.vtkActor()
actor.SetMapper(mapper)

# Create a renderer
renderer = vtk.vtkRenderer()
renderer.AddActor(actor)
renderer.SetBackground(0.1, 0.2, 0.4)

# Create a render window
render_window = vtk.vtkRenderWindow()
render_window.AddRenderer(renderer)

# Create an interactor
interactor = vtk.vtkRenderWindowInteractor()
interactor.SetRenderWindow(render_window)

# Start the interaction
interactor.Initialize()
interactor.Start()
