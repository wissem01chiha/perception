//utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP
#include<vector>
#include<string>
 
 
/**
 * @brief represents a point in 3D cartesian space.
 * @param x  x coordiante 
 * @param y  y-corrdinate 
 * @param z  z-coordinate
*/
struct point3D
{
    static double x ;
    static double y ;
    static double z ;
};

/**
 * @brief Data structure that will handle the input/output data stream 
 *        for the simulation
 * @param arry2csv member function  : 
*/
struct  Data
{
    
    /**
     * @brief write an array of double precsion in a csv format file 
     * @param array        - array of double
     * @param filename     - name of the output file .csv type 
    */
    static void array2csv(const std::vector<double>& array, const std::string& filename);
};











#endif