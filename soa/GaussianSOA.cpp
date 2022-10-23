//
// Created by xxmid on 23/10/2022.
//

#include "../includes/common.h"
#include "../includes/BmpSOA.h"

void    applyTransformation(BmpSOA &bmpImg, int x, int y)
{
    //std::vector<std::vector<ColorAOS>>   pixelKernel[5][5];
    float result[3] = {0.0f, 0.0f, 0.0f};
    std::vector<u_char> buffPixel;
    const std::vector<std::vector<float>> matrix = {
            {1.0f,4.0f,7.0f,4.0f,1.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {7.0f,26.0f,41.0f,26.0f,7.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {1.0f,4.0f,7.0f,4.0f,1.0f}
    };

    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {

            buffPixel = ((x + i >= 0) && (y + j >= 0) && ((x + i) < (int)bmpImg.GetWidth()) && ((y + j) < (int)bmpImg.GetHeight())) ? bmpImg.GetColorOnChannels(x + i, y + j) : std::vector<u_char>(3, 0);

            float floatingPixels[3] = {
                    (float)(buffPixel[bmpImg.CHAN_R]) / 255.0f,
                    (float)(buffPixel[bmpImg.CHAN_G]) / 255.0f,
                    (float)(buffPixel[bmpImg.CHAN_B]) / 255.0f,
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

    bmpImg.SetColor(std::vector<u_char>{static_cast<unsigned char>((append[0] / 273.0f) * 255.0f),
                             static_cast<unsigned char>((append[1] / 273.0f) * 255.0f),
                             static_cast<unsigned char>((append[2] / 273.0f) * 255.0f)
                            }
    , x, y);
}

int gaussianTransformation(BmpSOA& bmpImg)
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