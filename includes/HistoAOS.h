//
// Created by jmjon on 19/10/2022.
//

#ifndef ARCOS_PROJECT1_HISTOAOS_H
#define ARCOS_PROJECT1_HISTOAOS_H

#include "common.h"


struct N_Colors
{
    int r = 0;
    int g = 0;
    int b = 0;
};

class HistoAOS {
public:
    void write(std::string filename);
    void count_colors();
    int histogram(BmpAOS file, std::string filename);
    std::vector<N_Colors> n_colors;
    int m_width{};
    int m_height{};
    std::vector<ColorAOS> m_colors;

};


#endif //ARCOS_PROJECT1_HISTOAOS_H
