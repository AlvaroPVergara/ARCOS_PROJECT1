//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

int main (int argc, char *argv[])
{
    //TODO: Remove debug printss
    std::cout << "SOA INIT" << std::endl;
    if (ArgParser(argc, argv) < 0)
    {
        return (-1);
    }
    return (0);
}