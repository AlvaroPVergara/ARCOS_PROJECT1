//
// Created by middiz on 20/10/22.
//

#include "../includes/common.h"
#include "../includes/BmpAOS.h"


void    applyTransformation(BmpAOS &bmp_img, int x, int y)
{
    //std::vector<std::vector<ColorAOS>>   pixelKernel[5][5];
    float result[3] = {0.0f, 0.0f, 0.0f};
    ColorAOS buff_pixel;
    const std::vector<std::vector<float>> matrix = {
            {1.0f,4.0f,7.0f,4.0f,1.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {7.0f,26.0f,41.0f,26.0f,7.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {1.0f,4.0f,7.0f,4.0f,1.0f}
    };

    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {

            buff_pixel = ((x + i >= 0) && (y + j >= 0) && ((x + i) < (int)bmp_img.GetWidth()) && ((y + j) < (int)bmp_img.GetHeight())) ? bmp_img.GetColor(x + i, y + j) : ColorAOS(0, 0, 0);

            float floating_pixels[3] = {
                    (float)(buff_pixel.r) / 255.0f,
                    (float)(buff_pixel.g) / 255.0f,
                    (float)(buff_pixel.b) / 255.0f,
            };

            result[0] += static_cast<float>(matrix[i + 2][j + 2] * floating_pixels[0]);
            result[1] += static_cast<float>(matrix[i + 2][j + 2] * floating_pixels[1]);
            result[2] += static_cast<float>(matrix[i + 2][j + 2] * floating_pixels[2]);
        }
    }


    float append[3] = {result[0], result[1], result[2]};

    result[0] = 0;
    result[1] = 0;
    result[2] = 0;

    bmp_img.SetColor(ColorAOS(static_cast<unsigned char>((append[0] / 273.0f) * 255.0f),
                              static_cast<unsigned char>((append[1] / 273.0f) * 255.0f),
                              static_cast<unsigned char>((append[2] / 273.0f) * 255.0f)
                                    ), x, y);
}

int gaussianTransformation(BmpAOS& bmp_img)
{
    for (int y = 0; y < (int)bmp_img.GetHeight(); y++)
    {
        for (int x = 0; x < (int)bmp_img.GetWidth(); x++)
        {
            applyTransformation(bmp_img, x, y);
        }
    }
    return (0);
}