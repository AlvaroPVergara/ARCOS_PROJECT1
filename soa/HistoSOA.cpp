//
// Created by jmjon on 17/10/2022.
//

#include "../includes/common.h"
#include "../includes/HistoSOA.h"

void HistoSOA::write(std::string filename)
{
    std::fstream outfile;
    outfile.open(filename, std::ios_base::out);

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors.r[i]<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors.g[i]<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors.b[i]<<std::endl;
    }
}

void HistoSOA::count_colors()
{
    int r,g,b;

    for ( int i = 0; i<m_width*m_height; i++){
        r = m_colors.redChannel[i] * 255.0f;
        n_colors.r[r] += 1;

        g = m_colors.greenChannel[i] * 255.0f;
        n_colors.g[g] += 1;

        b = m_colors.blueChannel[i] * 255.0f;
        n_colors.b[b] += 1;
    }
}

int HistoSOA::histogram(BmpSOA file, std::string filename)
{
    m_colors = file.GetMColors();
    m_width = file.GetWidth();
    m_height = file.GetHeight();

    n_colors.r.resize(256);
    n_colors.b.resize(256);
    n_colors.g.resize(256);

    count_colors();
    write(filename);

    return 0;
}
