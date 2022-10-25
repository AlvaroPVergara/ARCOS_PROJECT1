//
// Created by xxmid on 02/10/2022.
//
#include "../includes/common.h"

void print_format()
{
    std::cout << "\timage in_path out_path oper" << std::endl;
    std::cout << "\t\toperation: copy, histo, mono, gauss" << std::endl;
}


//This function checks that the 3º argument given is one of the four needed for the program
int check_last_arg(const std::string& lastarg)
{
    if (lastarg == "copy" or lastarg == "histo" or lastarg == "mono" or lastarg == "gauss")
    {
        return (0);
    }
    else{
        std::cout << "Unexpected Operation: " << lastarg << std::endl;
        print_format();
        return (-1);
    }
}


//This function will check if a certain directory exists
//directory is the path to the directory to check
//type equals 0 if the directory is for input and equals 1 if
//the directory is for output
int check_dir(const std::string& directory, int type)
{
    if (!std::filesystem::exists(directory))
    {
        std::cout << "Input path: "<< directory << std::endl;
        std::cout << "Output path: "<< directory << std::endl;

        if(type==0)
        {
            std::cout << "Cannot open directory ["<< directory <<"]" << std::endl;
        }
        else if(type==1)
        {
            std::cout << "Output directory ["<< directory <<"] does not exist" << std::endl;
        }
        print_format();
        return(-1);
    }
    return(0);
}



int ArgParser (int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Wrong format:" << std::endl;
        print_format();
        return (-1);
    }
    if (check_last_arg(argv[3])<0)
    {
        return (-1);
    }
    if (check_dir(argv[1],0)<0)
    {
        return (-1);
    }
    if (check_dir(argv[2],1)<0)
    {
        return (-1);
    }
    std::cout << "Input path: "<< argv[1] << std::endl;
    std::cout << "Output path: "<< argv[2] << std::endl;
    return (0);
}