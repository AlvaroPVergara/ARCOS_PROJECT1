//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"
#include "../includes/aos.h"
#include "../includes/HistoAOS.h"
#include "MonoAOS.cpp"

void execute_function(const std::filesystem::path& filePath, std::filesystem::path pathOutDir, int(*function)(BmpAOS&)){
    BmpAOS bmp;
    std::string prefix = "new_";
    bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);
    std::cout << out_path / filePath.filename() << std::endl;

    function(bmp);

    std::cout << "Exportando imagen"<< std::endl;
    if (bmp.Export(out_path / filePath.filename()) < 0)
    {
        exit(-1);
    }
}

void execute_histo(const std::filesystem::path& filePath, std::filesystem::path pathOutDir){
    BmpAOS bmp;
    HistoAOS hs;

    std::string prefix = "new_";
    bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);
    std::filesystem::path new_filename = filePath.filename().replace_extension(".txt");
    std::string new_path = out_path.generic_string()+"/HistoAOS-"+ new_filename.generic_string();
    std::cout << new_path << std::endl;

    if (hs.histogram(bmp,new_path)<0){
        std::cerr<< "Failed creating histo" << std::endl;
    }
}


int functionality(std::vector<std::filesystem::path>BmpPaths, std::string lastarg,std::filesystem::path endpath ){
    for (const auto &path :BmpPaths)
    {
        if (lastarg=="copy"){
            FileCopy(path, endpath);
        }

        else if (lastarg=="histo"){
            execute_histo(path,endpath);
        }

        else if (lastarg=="gauss"){
            execute_function(path,endpath, gaussianTransformation);
        }
        else if (lastarg=="mono"){
            execute_function(path,endpath,MonoAOS);
        }

    }
    return (0);
}

