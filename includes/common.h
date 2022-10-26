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
#include <cmath>
#include <chrono>

typedef unsigned char u_char;
typedef unsigned int u_int;
int ArgParser (int argc, char *argv[]);
std::vector<std::filesystem::path> GetBmpPaths(std::string path);
int FileCopy(const std::filesystem::path& source, const std::filesystem::path& target);
int Functionality(const std::vector<std::filesystem::path>&bmp_paths, const std::string& lastarg, const std::filesystem::path& endpath );
void LinearTransformation(float ni[3], float ci[3]);
void Gamma(float gi[3], float cl);
void OutputStatistics(const std::filesystem::path &path, std::vector<long long int> times, std::string command);

#endif //ARCOS_PROJECT1_COMMON_H
