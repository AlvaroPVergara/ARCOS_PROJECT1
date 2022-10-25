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

typedef unsigned char u_char;
typedef unsigned int u_int;
int ArgParser (int argc, char *argv[]);
std::vector<std::filesystem::path> GetBmpPaths(std::string path);
int FileCopy(const std::filesystem::path& source, const std::filesystem::path& target);
int functionality(std::vector<std::filesystem::path>BmpPaths, std::string lastarg,std::filesystem::path endpath );

#endif //ARCOS_PROJECT1_COMMON_H
