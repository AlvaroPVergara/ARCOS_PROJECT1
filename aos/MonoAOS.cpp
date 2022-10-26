//
// Created by marta on 21/10/2022.
//
#include "../includes/common.h"
#include "../includes/BmpAOS.h"

long long int MonoAOS(BmpAOS& file)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    int m_width , m_height;
    float cl;
    float ni[3],ci[3], gi[3];
    std::vector<ColorAOS>&m_colors = file.GetMColors();
    m_width = file.GetWidth();
    m_height = file.GetHeight();

    for(int i=0; i<m_width * m_height; i++){
        //paso 1: Normalización
        ni[0] = m_colors[i].r;
        ni[1] = m_colors[i].g;
        ni[2] = m_colors[i].b;
        //paso 2: Transformacion a intensidad lineal
        LinearTransformation(ni,ci);
        //Paso 3: transformación lineal
        cl = 0.2126 * ci[0] + 0.7152 * ci[1] + 0.0722 * ci[2];
        //Corrección gamma
        Gamma(gi,cl);
        //Desnormalización
            m_colors[i].r = gi[0];
            m_colors[i].g = gi[1];
            m_colors[i].b = gi[2];
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}