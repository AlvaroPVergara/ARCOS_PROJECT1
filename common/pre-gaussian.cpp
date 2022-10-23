//
// Created by middiz on 20/10/22.
//

#include "../includes/common.h"
#include "../includes/BmpAOS.h"


void    applyTransformation(BmpAOS &bmpImg, int x, int y)
{
    //std::vector<std::vector<ColorAOS>>   pixelKernel[5][5];
    float result[3] = {0.0f, 0.0f, 0.0f};
    ColorAOS buffPixel;
    const std::vector<std::vector<float>> matrix = {
            {1.0f,4.0f,7.0f,4.0f,1.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {7.0f,26.0f,41.0f,26.0f,7.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {1.0f,4.0f,7.0f,4.0f,1.0f}
    };

    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {

            buffPixel = ((x + i >= 0) && (y + j >= 0) && ((x + i) < (int)bmpImg.GetWidth()) && ((y + j) < (int)bmpImg.GetHeight())) ? bmpImg.GetColor(x + i, y + j) : ColorAOS(0, 0, 0);

            float floatingPixels[3] = {
                    (float)(buffPixel.r) / 255.0f,
                    (float)(buffPixel.g) / 255.0f,
                    (float)(buffPixel.b) / 255.0f,
            };

            result[0] += static_cast<float>(matrix[i + 2][j + 2] * floatingPixels[0]);
            result[1] += static_cast<float>(matrix[i + 2][j + 2] * floatingPixels[1]);
            result[2] += static_cast<float>(matrix[i + 2][j + 2] * floatingPixels[2]);
        }
    }


    float append[3] = {result[0], result[1], result[2]};

    result[0] = 0;
    result[1] = 0;
    result[2] = 0;

    bmpImg.SetColor(ColorAOS(static_cast<unsigned char>((append[0] / 273.0f) * 255.0f),
                             static_cast<unsigned char>((append[1] / 273.0f) * 255.0f),
                             static_cast<unsigned char>((append[2] / 273.0f) * 255.0f)
                                    ), x, y);
}

int gaussianTransformation(BmpAOS& bmpImg)
{
    for (int y = 0; y < (int)bmpImg.GetHeight(); y++)
    {
        for (int x = 0; x < (int)bmpImg.GetWidth(); x++)
        {
            applyTransformation(bmpImg, x, y);
        }
    }
    return (0);
}