//
// Created by marta on 22/10/2022.
//
#include "../includes/common.h"
#include "../includes/BmpSOA.h"

long long int MonoSOA(BmpSOA& file)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    ColorSOA& m_colors = file.GetMColors();
    int m_width , m_height;
    float cl;
    float ni[3],ci[3], gi[3];
    m_width = file.GetWidth();
    m_height = file.GetHeight();

    for(int i=0; i<m_width * m_height; i++){

        //paso 1: Normalización
        ni[0] = m_colors.redChannel[i];
        ni[1] = m_colors.greenChannel[i];
        ni[2] = m_colors.blueChannel[i];

        //paso 2: Transformacion a intensidad lineal
        LinearTransformation(ni,ci);
        //Paso 3: transformación lineal
        cl = 0.2126 * ci[0] + 0.7152 * ci[1] + 0.0722 * ci[2];
        //Corrección gamma
        Gamma(gi,cl);
        //Desnormalización
        m_colors.redChannel[i] = gi[0];
        m_colors.greenChannel[i] = gi[1];
        m_colors.blueChannel[i] = gi[2];
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}