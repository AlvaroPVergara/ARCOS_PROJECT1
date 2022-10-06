//
// Created by xxmid on 02/10/2022.
//
#include "../includes/common.h"

void print_format()
{
    std::cout << "\timage in_path out_path oper" << std::endl;
    std::cout << "\t\toperation: copy, histo, mono, gauss" << std::endl;
}

int arg_parser (int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Wrong format:" << std::endl;
        print_format();
        return (-1);
    }
    // Seguir parseando
    return (0);
}