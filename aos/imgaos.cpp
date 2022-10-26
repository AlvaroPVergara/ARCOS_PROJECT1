//
// Created by Alvar on 25/10/2022.
//
#include "../includes/common.h"


int main (int argc, char *argv[])
{
    std::vector<std::filesystem::path> bmp_paths;
    if (ArgParser(argc, argv) < 0)
        return (-1);
    bmp_paths = GetBmpPaths(argv[1]);
    if (bmp_paths.empty()){
        std::cerr << "No hay ninguna imagen bmp en el directorio de entrada" << std::endl;
    }

    if (Functionality(bmp_paths, static_cast<std::string>(argv[3]), static_cast<std::filesystem::path>(argv[2])) < 0){
        return (-1);
    }
    return (0);
}