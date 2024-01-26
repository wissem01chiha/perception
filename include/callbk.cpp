#include"callbk.hpp"
#include <GL/gl.h>
#include <GL/glu.h>

 


void callbk::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
// If yoffset is positive, zoom in
    if (yoffset > 0)
    {
        zoom += zoom_speed;
        // Clamp the zoom factor to the maximum value
        if (zoom > max_zoom)
        {
            zoom = max_zoom;
        }
    }
    // If yoffset is negative, zoom out
    else if (yoffset < 0)
    {
        zoom -= zoom_speed;
        // Clamp the zoom factor to the minimum value
        if (zoom < min_zoom)
        {
            zoom = min_zoom;
        }
    }

    // Use the zoom factor to modify the projection matrix or the camera position
    // For example, if you are using a perspective projection, you can do something like this
    // Note: this assumes you have a global variable called window_width and window_height
    // that store the current size of the window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0 * zoom, (double)window_width / (double)window_height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
   
}
void callbk::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;     
        glfwGetCursorPos(window, &xpos, &ypos); 

        // [...]
    }}