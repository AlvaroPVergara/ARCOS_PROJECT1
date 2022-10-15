//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

std::vector<std::filesystem::path> checkbmp(std::string path)
{
    std::vector <std::filesystem::path> bmpfiles;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension()=="bmp")
        {
            bmpfiles.push_back(entry.path());
        }
    }
    return (bmpfiles);
}