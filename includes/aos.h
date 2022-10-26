
//
// Created by xxmid on 06/10/2022.
//

#ifndef ARCOS_PROJECT1_AOS_H
#define ARCOS_PROJECT1_AOS_H
#include "BmpAOS.h"
#include "../includes/HistoAOS.h"

long long int GaussianTransformation(BmpAOS& bmp_img);
long long int MonoAOS(BmpAOS& file);
std::vector<long long int>
ExecuteFunction(const std::filesystem::path& file_path, const std::filesystem::path& path_out_dir, long long int(*function)(BmpAOS&));
// Redundant histo explanation necessary for exemplification of different implementations on AOS-SOA.
std::vector<long long int>
ExecuteHisto(const std::filesystem::path& file_path, const std::filesystem::path& path_out_dir);
long long int copy(BmpAOS& file);
#endif //ARCOS_PROJECT1_AOS_H
