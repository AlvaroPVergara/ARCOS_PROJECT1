//
// Created by jmjon on 19/10/2022.
//

#ifndef ARCOS_PROJECT1_HISTOSOA_H
#define ARCOS_PROJECT1_HISTOSOA_H

#include "common.h"
#include "BmpSOA.h"

struct NumberColors
{
    std::vector<int> r;
    std::vector<int> g;
    std::vector<int> b;
};

class HistoSOA {
public:
    void WriteHistogram(std::string filename);
    void CountColors();
    int Histogram(BmpSOA file, std::string filename);
    NumberColors n_colors;
    int m_width{};
    int m_height{};
    ColorSOA m_colors;

};
#endif //ARCOS_PROJECT1_HISTOSOA_H
