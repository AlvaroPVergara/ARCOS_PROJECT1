//
// Created by xxmid on 02/10/2022.
//

#include "../includes/common.h"

int main ()
{
    const int w = 640;
    const int h = 480;

    BmpAOS bmp(w, h);
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            bmp.SetColor(ColorAOS((float)x / (float)w, 1.0f - ((float)x / (float)w), (float)y / (float)h), x, y);
        }
    }
    bmp.Export("test.bmp");
    return (0);
}
