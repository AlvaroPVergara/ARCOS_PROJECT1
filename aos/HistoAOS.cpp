//
// Created by jmjon on 17/10/2022.
//

#include "../includes/common.h"
#include "../includes/BmpAOS.h"
#include "../includes/HistoAOS.h"

void HistoAOS::write(std::string filename)
{
    std::fstream outfile;
    outfile.open(filename, std::ios_base::out);

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors[i].r<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors[i].g<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors[i].b<<std::endl;
    }
}

void HistoAOS::count_colors()
{
    int r,g,b;

    for ( int i = 0; i<m_width*m_height; i++){

        r = m_colors[i].r * 255.0f;
        n_colors[r].r += 1;

        g = m_colors[i].g * 255.0f;
        n_colors[g].g += 1;

        b = m_colors[i].b * 255.0f;
        n_colors[b].b += 1;
    }
}

int HistoAOS::histogram(BmpAOS file, std::string filename)
{
    m_colors = file.GetMColors();
    m_width = file.GetWidth();
    m_height = file.GetHeight();

    n_colors.resize(256);

    count_colors();
    write(filename);

    return 0;
}

