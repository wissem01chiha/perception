#ifndef CALLBK_HPP
#define CALLBK_HPP

#include"GLFW/glfw3.h"
#include <iostream>
 
 
/**
 * @brief  scroll_callback 
 * @param window 
 * @param xoffset 
 * @param yoffset 
 */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
   std::cout << "hi";
}
 
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;     
        glfwGetCursorPos(window, &xpos, &ypos); 

        // [...]
    }
}




















#endif