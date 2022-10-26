//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"
#include "../includes/aos.h"
#include "../includes/HistoAOS.h"
#include "MonoAOS.cpp"


void OutputStatistics(const std::filesystem::path &path, std::vector<long long int> times, std::string command);

long long int copy(BmpAOS& file)
{return(file.emptyFlag);}

/*ExecuteFunction is used for execute the mono and gauss functions, it takes the path of the file (BMP)
 * and the exit directory for the path, it also takes what function it needs to be done
 * (MonoAOS/GaussianTransformation).*/
std::vector<long long int> ExecuteFunction(const std::filesystem::path& file_path, const std::filesystem::path& path_out_dir, long long int(*function)(BmpAOS&)){
    //First, it creates the BmpAos objet and fills it with the path given
    BmpAOS bmp;

    long long int time_read = bmp.Read(file_path);
    //Then it executes the third parameter function
    long long int time_exec = function(bmp);
    //When the function finishes it exports the Bmp file to the output directory
    long long int time_export = bmp.Export(path_out_dir / file_path.filename());
    return std::vector<long long int>{
            time_read,
            time_exec,
            time_export
    };
};

/*ExecuteHisto is the adapted version of ExecuteFunction to work with histograms.*/
std::vector<long long int> ExecuteHisto(const std::filesystem::path& file_path, const std::filesystem::path& path_out_dir){
    //Besides creating a Bmp object, it also creates an HistoAos objet
    BmpAOS bmp;
    HistoAOS hs;

    long long int time_read = bmp.Read(file_path);
    //For teh output file name, it will be the output directory plus the name of the file without
    //extension and then the changed extension to .txt
    std::filesystem::path new_filename = file_path.filename().replace_extension(".txt");
    std::string new_path = path_out_dir.generic_string() + "/HistoAOS-" + new_filename.generic_string();

    //Lastly it creates the histogram
    std::vector<long long int>time_exec_export = hs.Histogram(bmp,new_path);

    return std::vector<long long int>{
            time_read,
            time_exec_export[0],
            time_exec_export[1]
    };
}

/*Functionality takes a vector of BMP paths, then, for each path, it calls the execution function
 * that the user chooses in the input arguments*/
int Functionality(std::vector<std::filesystem::path>bmp_paths, std::string lastarg, std::filesystem::path endpath ){
    for (const auto &path :bmp_paths)
    {
        std::vector<long long int> times;
        if (lastarg=="copy"){
            /*
            FileCopy(path, endpath);
             */
            times = ExecuteFunction(path, endpath, copy);
        }

        else if (lastarg=="histo"){
            times = ExecuteHisto(path, endpath);
        }

        else if (lastarg=="gauss"){
            times = ExecuteFunction(path, endpath, GaussianTransformation);
        }
        else if (lastarg=="mono"){
            times = ExecuteFunction(path, endpath, MonoAOS);
        }
        OutputStatistics(path, times, lastarg);
    }
    return (0);
}

void OutputStatistics(const std::filesystem::path &path, std::vector<long long int> times, std::string command) {
    long long int total_time = times[0] + times[1] + times[2];

    std::cout << "File: \"" << path.string() << "\"(time: "<< total_time << ")" << std::endl;
    std::cout << "\tLoad time: " << times[0] << std::endl;
    // Capitalize first letter as in the pdf.
    command[0] = toupper(command[0]);
    std::cout << "\t" << command << " time: " << times[1] << std::endl;
    std::cout << "\tStore time: "<< times[2] << std::endl;
}

