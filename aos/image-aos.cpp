//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"
#include "../includes/aos.h"


void trabaja(const std::filesystem::path& filePath, char *pathOutDir){
    BmpAOS bmp;

    std::string prefix = "new_";
    bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);
    std::cout << out_path / filePath.filename() << std::endl;
    gaussianDiffusion(bmp);
    if (bmp.Export(out_path / filePath.filename()) < 0)
    {
        exit(-1);
    }
}

int functionality(std::vector<std::filesystem::path>BmpPaths, std::string lastarg,std::filesystem::path endpath ){
    for (const auto &path :BmpPaths)
    {
        if (lastarg=="copy"){
            FileCopy(path, endpath);
        }
    }
    return (0);
}


int main (int argc, char *argv[])
{

    std::vector<std::filesystem::path> BmpPaths;
    if (ArgParser(argc, argv) < 0)
        return (-1);
    BmpPaths = GetBmpPaths(argv[1]);


    for (const auto &path : BmpPaths) {
        trabaja(path, argv[2]);
    }
    /*
    if (functionality(BmpPaths, static_cast<std::string>(argv[3]), static_cast<std::filesystem::path>(argv[2]))<0){
        return (-1);
    }
    */    return (0);
}
