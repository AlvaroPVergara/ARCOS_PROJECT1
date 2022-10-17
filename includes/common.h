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
#include "BmpAOS.h"

int ArgParser (int argc, char *argv[]);
std::vector<std::filesystem::path> CheckBmp(std::string path);
int FileCopy(const std::filesystem::path& source, const std::string& target);

#endif //ARCOS_PROJECT1_COMMON_H
