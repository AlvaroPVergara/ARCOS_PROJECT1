//
// Created by middiz on 20/10/22.
//

#include "../includes/common.h"
#include "../includes/BmpAOS.h"


void apply_mascara(BmpAOS& bmpFile, const int mascara[5][5], int x, int y) {
    float new_color_r=0;
    float new_color_g=0;
    float new_color_b=0;
    float pixel_color_r;
    float pixel_color_g;
    float pixel_color_b;

    for (int s = -2; s < 3; s++) {
        for (int t = -2; t < 3; t++) {
            if ((x + s) < 0 || (y + t) < 0 ||
                (x + s) > static_cast<int>(bmpFile.GetWidth()) ||
                (y + t) > static_cast<int>(bmpFile.GetHeight())) {
                pixel_color_r = 0;
                pixel_color_g = 0;
                pixel_color_b = 0;
                //std::cout << "Out of bounds" << std::endl;
            }
            else {
                pixel_color_r = static_cast<float>(bmpFile.GetColor(x + s, y + t).r) / 255.0f;
                pixel_color_g = static_cast<float>(bmpFile.GetColor(x + s, y + t).g) / 255.0f;
                pixel_color_b = static_cast<float>(bmpFile.GetColor(x + s, y + t).b) / 255.0f;
            }

            new_color_r += static_cast<float>(mascara[t + 2][s + 2]) * pixel_color_r;
            new_color_g += static_cast<float>(mascara[t + 2][s + 2]) * pixel_color_g;
            new_color_b += static_cast<float>(mascara[t + 2][s + 2]) * pixel_color_b;
        }
    }
    new_color_r = new_color_r / 273;

    new_color_g = new_color_g / 273;
    new_color_b = new_color_b / 273;

    /*
    std::cout << "Red: " << static_cast <int>(static_cast<u_char> (new_color_r * 255.0f)) << " Green: " << static_cast <int>(static_cast<u_char> (new_color_g * 255.0f))
        << " Blue: " << static_cast <int>(static_cast<u_char> (new_color_b * 255.0f)) << std::endl;*/

    ColorAOS nc = ColorAOS(static_cast<u_char> (new_color_r * 255.0f),
                           static_cast<u_char> (new_color_g * 255.0f),
                           static_cast<u_char> (new_color_b * 255.0f));
    bmpFile.SetColor(nc, x, y);
}

int gaussianDiffusion(BmpAOS bmpFile){
    ColorAOS new_color;
    std::cout << "Difuminando" <<std::endl;
    const int mascara[5][5] = {
             {1, 4,  7,  4,  1},
             {4, 16, 26, 16, 4},
             {7, 26,41,26,7},
             {4, 16,26,16,4},
             {1, 4, 7, 4, 1}
    };

    for (int y = 0; y < static_cast<int>(bmpFile.GetHeight()); y++) {
        for (int x = 0; x < static_cast<int>(bmpFile.GetWidth()); x++) {
            /*std::cout << "Applying mascara to x: " << x << " y: " << y << std::endl;*/
            apply_mascara(bmpFile, mascara, x, y);
        }
    }
    return (0);
}