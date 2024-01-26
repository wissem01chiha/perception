#ifndef CALLBK_HPP
#define CALLBK_HPP

#include"../glfw/include/GLFW/glfw3.h"

/**
 * @brief 
 */
struct callbk
{
 
   static float zoom          ;
   static float zoom_speed    ;
   static float min_zoom      ;
   static float max_zoom      ;
   static int   window_width  ;
   static int   window_height ;

 
    
   /**
    * @brief 
    * @param window 
    * @param xoffset 
    * @param yoffset 
    */
   static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

   /**
    * @brief 
    * @param window 
    * @param button 
    * @param action 
    * @param mods 
    */
   static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

  
};
 

















#endif