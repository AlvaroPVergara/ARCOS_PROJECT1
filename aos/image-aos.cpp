//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"
#include "../includes/aos.h"
#include "../includes/HistoAOS.h"

void execute_function(const std::filesystem::path& filePath, std::filesystem::path pathOutDir, int(*function)(BmpAOS)){
    BmpAOS bmp;


    std::string prefix = "new_";
    bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);
    std::cout << out_path / filePath.filename() << std::endl;

    //TODO:CHANGE THE WAY THIS IS DONE
    function(bmp);
    //HistoAOS::histogram(bmp,"D:\\Universidad\\ARCOS_PROJECT1\\test\\in_fold\\sample");
    std::cout << "Exportando imagen"<< std::endl;
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
        /*
        else if (lastarg=="histo"){
            execute_function(path,endpath, HistoAOS::histogram);
        }
        */
        else if (lastarg=="gauss"){
            execute_function(path,endpath, gaussianDiffusion);
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
    if (BmpPaths.empty()){
        std::cerr << "No hay ninguna imagen bmp en el directorio de entrada" << std::endl;
    }

    if (functionality(BmpPaths, static_cast<std::string>(argv[3]), static_cast<std::filesystem::path>(argv[2]))<0){
        return (-1);
    }
    return (0);
}
