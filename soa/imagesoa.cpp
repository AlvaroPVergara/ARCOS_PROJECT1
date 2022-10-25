//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"
#include "../includes/soa.h"
#include "../includes/HistoSOA.h"
#include "MonoSOA.cpp"

void execute_function(const std::filesystem::path& filePath, std::filesystem::path pathOutDir, int(*function)(BmpSOA&)){
    BmpSOA bmp;
    std::string prefix = "new_";
    bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);

    function(bmp);

    if (bmp.Export(out_path / filePath.filename()) < 0)
    {
        exit(-1);
    }
}

void ExecuteHisto(const std::filesystem::path& file_path, std::filesystem::path path_out_dir){
    BmpSOA bmp;
    HistoSOA hs;

    std::string prefix = "new_";
    bmp.Read(file_path);

    std::filesystem::path out_path = std::filesystem::path(path_out_dir);
    std::filesystem::path new_filename = file_path.filename().replace_extension(".txt");
    std::string new_path = out_path.generic_string()+"/HistoSOA-"+ new_filename.generic_string();

    if (hs.histogram(bmp,new_path)<0){
        std::cerr<< "Failed creating histo" << std::endl;
    }
}


int Functionality(std::vector<std::filesystem::path>BmpPaths, std::string lastarg, std::filesystem::path endpath ){
    for (const auto &path :BmpPaths)
    {
        if (lastarg=="copy"){
            FileCopy(path, endpath);
        }

        else if (lastarg=="histo"){
            ExecuteHisto(path, endpath);
        }
        else if (lastarg=="gauss"){
            execute_function(path,endpath, gaussianTransformation);
        }
        else if (lastarg=="mono"){
            execute_function(path,endpath,MonoSOA);
        }

    }
    return (0);
}