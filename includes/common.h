//
// Created by xxmid on 02/10/2022.
//


#ifndef ARCOS_PROJECT1_COMMON_H
#define ARCOS_PROJECT1_COMMON_H

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include "Bmp.h"

int arg_parser (int argc, char *argv[]);
std::vector<std::filesystem::path> checkbmp(std::string path);
int FileCopy(std::filesystem::path source, std::string target);

#endif //ARCOS_PROJECT1_COMMON_H
