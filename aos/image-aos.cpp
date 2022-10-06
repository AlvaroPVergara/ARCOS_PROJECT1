//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

int main (int argc, char *argv[])
{
    //TODO: Remove debug printss
    std::cout << "AOS INIT" << std::endl;
    if (arg_parser(argc, argv) < 0)
    {
        return (-1);
    }
    return (0);
}
