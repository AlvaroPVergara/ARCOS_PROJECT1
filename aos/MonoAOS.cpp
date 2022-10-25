//
// Created by marta on 21/10/2022.
//
#include "../includes/common.h"
#include "../includes/BmpAOS.h"



int MonoAOS(BmpAOS& file)
{
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
    //std::cout << m_colors[3].r << "pixel 3 rojo" <<std::endl;
    return 0;
}