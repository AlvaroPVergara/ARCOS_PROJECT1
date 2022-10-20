//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"
#include "../includes/aos.h"

void trabaja(const std::filesystem::path& filePath, char *pathOutDir, void (*func)(BmpAOS)){
    BmpAOS bmp;

    std::string prefix = "new_";
    bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);
    std::cout << out_path / filePath.filename() << std::endl;

    func(bmp);

    bmp.Export(out_path / filePath.filename());
}

int functionality(std::vector<std::filesystem::path>BmpPaths, std::string lastarg,std::filesystem::path endpath ){
    for (const auto &BMP :BmpPaths)
    {
        if (lastarg=="copy"){
            FileCopy(BMP, endpath);
        }
        if (lastarg=="gauss");
            trabaja(path1, path2, gaus)
    }
    return (0);
}


int main (int argc, char *argv[])
{
    std::vector<std::filesystem::path> BmpPaths;
    if (ArgParser(argc, argv) < 0)
        return (-1);
    BmpPaths = GetBmpPaths(argv[1]);

    /*
    for (const auto &path : BmpPaths) {
        trabaja(path);
    }*/

    if (functionality(BmpPaths, static_cast<std::string>(argv[3]), static_cast<std::filesystem::path>(argv[2]))<0){
        return (-1);
    }

    return (0);
}
