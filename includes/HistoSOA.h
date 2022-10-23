//
// Created by jmjon on 19/10/2022.
//

#ifndef ARCOS_PROJECT1_HISTOSOA_H
#define ARCOS_PROJECT1_HISTOSOA_H

#include "common.h"
#include "BmpSOA.h"

struct N_Colors
{
    std::vector<int> r;
    std::vector<int> g;
    std::vector<int> b;
};

class HistoSOA {
public:
    void write(std::string filename);
    void count_colors();
    int histogram(BmpSOA file, std::string filename);
    N_Colors n_colors;
    int m_width{};
    int m_height{};
    ColorSOA m_colors;

};
#endif //ARCOS_PROJECT1_HISTOSOA_H
