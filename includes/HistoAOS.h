//
// Created by jmjon on 19/10/2022.
//

#ifndef ARCOS_PROJECT1_HISTOAOS_H
#define ARCOS_PROJECT1_HISTOAOS_H

#include "common.h"


struct NumberColors
{
    int r = 0;
    int g = 0;
    int b = 0;
};

class HistoAOS {
public:
    void WriteHistogram(std::string filename);
    void CountColors();
    int Histogram(BmpAOS file, std::string filename);
    std::vector<NumberColors> n_colors;
    int m_width{};
    int m_height{};
    std::vector<ColorAOS> m_colors;
};


#endif //ARCOS_PROJECT1_HISTOAOS_H
