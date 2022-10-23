//
// Created by marta on 21/10/2022.
//
#include "../includes/common.h"
#include "../includes/BmpAOS.h"
#include <math.h>

void LinearTransformation(float ni[3], float ci[3])
{
    for (int e=0; e<=2; e++){
        if (ni[e] <= 0.04045){
            ci[e] = ni[e]/12.92;
        }
        else{
            ci[e] = pow(((ni[e]+0.055)/1.055),2.4);
        }
    }
}

void Gamma(float gi[3], float cl)
{
    for (int o=0; o<=2; o++){
        if (cl <= 0.0031308){
            gi[o] = 12.92*cl;
        }
        else{
            gi[o] = 1.055 * pow(cl,1/2.4) - 0.055;
        }
    }
}

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