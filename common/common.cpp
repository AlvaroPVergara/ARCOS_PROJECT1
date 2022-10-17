//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

std::vector<std::filesystem::path> GetBmpPaths(std::string path){
    std::vector <std::filesystem::path> bmpFiles;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == "bmp")
        {
            bmpFiles.push_back(entry.path());
        }
        else{
            std::cout << "Archivo " << entry.path() << " no tiene extension .bmp" << std::endl;
        }
    }
    return (bmpFiles);
}
