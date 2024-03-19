"""



"""
import numpy as np 
def get_line_by_2pts(x,y):
    x1 = np.array([x[0], y[0], 1]).reshape(-1, 1)
    x2 = np.array([x[1], y[1], 1]).reshape(-1, 1)
    l =  np.cross(x1,x2)
    l =l /np.sqrt(l(0)**2+l(1)**2+l(2)**2)
    return l