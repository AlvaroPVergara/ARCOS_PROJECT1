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
    //TODO: add read function to BMPSOA
    //bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);
    std::cout << out_path / filePath.filename() << std::endl;

    function(bmp);

    std::cout << "Exportando imagen"<< std::endl;
    /*TODO: add Export function to BMPSOA
    if (bmp.Export(out_path / filePath.filename()) < 0)
    {
        exit(-1);
    }*/
}

void execute_histo(const std::filesystem::path& filePath, std::filesystem::path pathOutDir){
    BmpSOA bmp;
    HistoSOA hs;

    std::string prefix = "new_";
    //TODO: add read function to BMPSOA
    //bmp.Read(filePath);

    std::filesystem::path out_path = std::filesystem::path(pathOutDir);
    std::filesystem::path new_filename = filePath.filename().replace_extension(".txt");
    std::string new_path = out_path.generic_string()+"/"+ new_filename.generic_string();
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
        /*TODO: apply gaussianSOA function
        else if (lastarg=="gauss"){
            execute_function(path,endpath, gaussianTransformation);
        }*/
        else if (lastarg=="mono"){
            execute_function(path,endpath,MonoSOA);
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