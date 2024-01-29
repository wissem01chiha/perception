//utils.cpp
#include"utils.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
 
using namespace std;
 

double point3D::x = .0;
double point3D::y = .0;
double point3D::z = .0;

void Data::array2csv(const std::vector<double>& array, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (size_t i = 0; i < array.size(); ++i) {
            file << array[i];
            if (i < array.size() - 1) {
                file << ",";
            }
        }
        file.close();
        std::cout << "Data written to " << filename << " successfully." << std::endl;
    }
    else{
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }
}





 