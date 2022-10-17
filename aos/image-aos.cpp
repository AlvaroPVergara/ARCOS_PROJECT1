//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

void trabaja(std::filesystem::path filePath){
    BmpAOS bmp;

    std::string prefix = "new_";
    bmp.Read(filePath.string().c_str());
    bmp.Export( prefix.append(filePath.string()).c_str());
}

int main (int argc, char *argv[])
{
    std::vector<std::filesystem::path> BmpPaths;
    if (ArgParser(argc, argv) < 0)
        return (-1);
    BmpPaths = GetBmpPaths(argv[1]);
    for (const auto &path : BmpPaths){
        trabaja(path);
    }
    return (0);
}
