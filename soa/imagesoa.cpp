//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"
#include "../includes/soa.h"
#include "../includes/HistoSOA.h"
#include "MonoSOA.cpp"


/*ExecuteFunction is used for execute the mono and gauss functions, it takes the path of the file (BMP)
 * and the exit directory for the path, it also takes what function it needs to be done
 * (MonoSOA/GaussianTransformation).*/
void execute_function(const std::filesystem::path& file_path, std::filesystem::path path_out_dir, int(*function)(BmpSOA&)){
    //First, it creates the BmpSOA objet and fills it with the path given
    BmpSOA bmp;
    std::string prefix = "new_";
    bmp.Read(file_path);

    //Then it executes the third parameter function
    function(bmp);

    //When the function finishes it exports the Bmp file to the output directory
    if (bmp.Export(path_out_dir / file_path.filename()) < 0)
    {
        exit(-1);
    }
}

/*ExecuteHisto is the adapted version of ExecuteFunction to work with histograms.*/
void ExecuteHisto(const std::filesystem::path& file_path, std::filesystem::path path_out_dir){
    //Besides creating a Bmp object, it also creates an HistoAos objet
    BmpSOA bmp;
    HistoSOA hs;

    std::string prefix = "new_";
    bmp.Read(file_path);

    //For teh output file name, it will be the output directory plus the name of the file without
    //extension and then the changed extension to .txt
    std::filesystem::path new_filename = file_path.filename().replace_extension(".txt");
    std::string new_path = path_out_dir.generic_string()+"/HistoSOA-"+ new_filename.generic_string();

    //Lastly it creates the histogram
    if (hs.histogram(bmp,new_path)<0){
        std::cerr<< "Failed creating histo" << std::endl;
    }
}

/*Functionality takes a vector of BMP paths, then, for each path, it calls the execution function
 * that the user chooses in the input arguments*/
int Functionality(std::vector<std::filesystem::path>bmp_paths, std::string lastarg, std::filesystem::path endpath ){
    for (const auto &path :bmp_paths)
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