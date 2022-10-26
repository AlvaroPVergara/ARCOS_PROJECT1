//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

std::vector<std::filesystem::path> GetBmpPaths(std::string path){
    std::vector <std::filesystem::path> bmp_files;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == ".bmp")
        {
            bmp_files.push_back(entry.path());
        }
    }
    return (bmp_files);
}


void LinearTransformation(float ni[3], float ci[3])
{
    for (int e=0; e<=2; e++){
        if (ni[e] <= 0.04045){
            ci[e] = ni[e]/12.92;
        }
        else{
            ci[e] = pow(((ni[e]+0.055)/1.055),2.4);
        }
    }
}

void Gamma(float gi[3], float cl)
{
    for (int o=0; o<=2; o++){
        if (cl <= 0.0031308){
            gi[o] = 12.92*cl;
        }
        else{
            gi[o] = 1.055 * pow(cl,1/2.4) - 0.055;
        }
    }
}

