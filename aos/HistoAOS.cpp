//
// Created by jmjon on 17/10/2022.
//

#include "../includes/common.h"
#include "../includes/BmpAOS.h"
#include "../includes/HistoAOS.h"

long long int HistoAOS::write(std::string filename)
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::fstream outfile;
    outfile.open(filename, std::ios_base::out);
    if (!outfile.is_open()){
        std::cerr << "Error opening new txt file"<< std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile << i << ":" << n_colors[i].r << std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile << i << ":" << n_colors[i].g << std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile << i << ":" << n_colors[i].b << std::endl;
    }
    outfile.close();
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}

long long int HistoAOS::count_colors()
{
    int r, g, b;
    auto start_time = std::chrono::high_resolution_clock::now();

    for ( int i = 0; i < m_width*m_height; i++){

        r = m_colors[i].r;
        n_colors[r].r += 1;

        g = m_colors[i].g;
        n_colors[g].g += 1;

        b = m_colors[i].b;
        n_colors[b].b += 1;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}

std::vector<long long int> HistoAOS::histogram(BmpAOS file, std::string filename)
{
    m_colors = file.GetMColors();
    m_width = file.GetWidth();
    m_height = file.GetHeight();

    n_colors.resize(256);
    long long int func_time = count_colors();
    long long int export_time = write(filename);

    return {
        func_time,
        export_time
    };
}

