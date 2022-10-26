//
// Created by xxmid on 06/10/2022.
//

#ifndef ARCOS_PROJECT1_SOA_H
#define ARCOS_PROJECT1_SOA_H

#include "BmpSOA.h"
#include "../includes/HistoSOA.h"

long long int GaussianTransformation(BmpSOA& bmp_img);
long long int MonoSOA(BmpSOA& file);
std::vector<long long int>
ExecuteFunction(const std::filesystem::path& file_path, const std::filesystem::path& path_out_dir, long long int(*function)(BmpSOA&));
// Redundant histo explanation necessary for exemplification of different implementations on AOS-SOA.
std::vector<long long int>
ExecuteHisto(const std::filesystem::path& file_path, const std::filesystem::path& path_out_dir);
long long int copy(BmpSOA& file);
#endif //ARCOS_PROJECT1_SOA_H
