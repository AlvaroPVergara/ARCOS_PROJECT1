//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

std::vector<std::filesystem::path> CheckBmp(std::string path)
{
    std::vector <std::filesystem::path> bmpFiles;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == "bmp")
        {
            bmpFiles.push_back(entry.path());
        }
    }
    return (bmpFiles);
}
