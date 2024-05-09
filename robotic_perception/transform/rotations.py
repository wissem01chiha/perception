import numpy as np

def rotation_matrix_x(angle):
    """
    Generate a rotation matrix around the x-axis.
    
    Args:
        angle (float): Angle in radians for rotation.
        
    Returns:
        numpy.ndarray: Rotation matrix.
    """
    rotation_matrix = np.array([[1, 0, 0],
                                [0, np.cos(angle), -np.sin(angle)],
                                [0, np.sin(angle), np.cos(angle)]])
    return rotation_matrix

def rotation_matrix_y(angle):
    """
    Generate a rotation matrix around the y-axis.
    
    Args:
        angle (float): Angle in radians for rotation.
        
    Returns:
        numpy.ndarray: Rotation matrix.
    """
    rotation_matrix = np.array([[np.cos(angle), 0, np.sin(angle)],
                                [0, 1, 0],
                                [-np.sin(angle), 0, np.cos(angle)]])
    return rotation_matrix

def rotation_matrix_z(angle):
    """
    Generate a rotation matrix around the z-axis.
    
    Args:
        angle (float): Angle in radians for rotation.
        
    Returns:
        numpy.ndarray: Rotation matrix.
    """
    rotation_matrix = np.array([[np.cos(angle), -np.sin(angle), 0],
                                [np.sin(angle), np.cos(angle), 0],
                                [0, 0, 1]])
    return rotation_matrix
    
def rotation_matrix_xy(x_angle, y_angle):
    """
    Generate a combined rotation matrix around the x and y axes.
    
    Args:
        x_angle (float): Angle in radians for rotation around x-axis.
        y_angle (float): Angle in radians for rotation around y-axis.
        
    Returns:
        numpy.ndarray: Combined rotation matrix.
    """
    return np.dot(rotation_matrix_x(x_angle), rotation_matrix_y(y_angle))

def rotation_matrix_xz(x_angle, z_angle):
    """
    Generate a combined rotation matrix around the x and z axes.
    
    Args:
        x_angle (float): Angle in radians for rotation around x-axis.
        z_angle (float): Angle in radians for rotation around z-axis.
        
    Returns:
        numpy.ndarray: Combined rotation matrix.
    """
    return np.dot(rotation_matrix_x(x_angle), rotation_matrix_z(z_angle))

def rotation_matrix_yz(y_angle, z_angle):
    """
    Generate a combined rotation matrix around the y and z axes.
    
    Args:
        y_angle (float): Angle in radians for rotation around y-axis.
        z_angle (float): Angle in radians for rotation around z-axis.
        
    Returns:
        numpy.ndarray: Combined rotation matrix.
    """
    return np.dot(rotation_matrix_y(y_angle), rotation_matrix_z(z_angle))

def rotation_matrix_xyz(x_angle, y_angle, z_angle):
    """
    Generate a combined rotation matrix around the x, y, and z axes.
    
    Args:
        x_angle (float): Angle in radians for rotation around x-axis.
        y_angle (float): Angle in radians for rotation around y-axis.
        z_angle (float): Angle in radians for rotation around z-axis.
        
    Returns:
        numpy.ndarray: Combined rotation matrix.
    """
    return np.dot(np.dot(rotation_matrix_x(x_angle), rotation_matrix_y(y_angle)), 
                  rotation_matrix_z(z_angle))
