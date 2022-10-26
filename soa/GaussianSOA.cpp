//
// Created by xxmid on 23/10/2022.
//

#include "../includes/common.h"
#include "../includes/BmpSOA.h"

void
ApplyTransformation(BmpSOA &bmp_img, const std::vector<std::vector<float>> &matrix, int x, int y)
{
    //std::vector<std::vector<ColorAOS>>   pixelKernel[5][5];
    float result[3] = {0.0f, 0.0f, 0.0f};
    std::vector<u_char> buff_pixel;

    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {

            buff_pixel = ((x + i >= 0) && (y + j >= 0) && ((x + i) < static_cast<int>(bmp_img.GetWidth())) && ((y + j) < static_cast<int>(bmp_img.GetHeight()))) ? bmp_img.GetColorOnChannels(x + i, y + j) : std::vector<u_char>(3, 0);

            float floating_pixels[3] = {
                    static_cast<float>(buff_pixel[bmp_img.CHAN_R]) / 255.0f,
                    static_cast<float>(buff_pixel[bmp_img.CHAN_G]) / 255.0f,
                    static_cast<float>(buff_pixel[bmp_img.CHAN_B]) / 255.0f,
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
    bmp_img.SetColor(std::vector<u_char>{static_cast<unsigned char>((append[0] / 273.0f) * 255.0f),
                                         static_cast<unsigned char>((append[1] / 273.0f) * 255.0f),
                                         static_cast<unsigned char>((append[2] / 273.0f) * 255.0f)
                            }
    , x, y);
}

long long int
GaussianTransformation(BmpSOA& bmp_img)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    const std::vector<std::vector<float>> matrix = {
            {1.0f,4.0f,7.0f,4.0f,1.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {7.0f,26.0f,41.0f,26.0f,7.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {1.0f,4.0f,7.0f,4.0f,1.0f}
    };
    for (int y = 0; y < static_cast<int>(bmp_img.GetHeight()); y++)
    {
        for (int x = 0; x < static_cast<int>(bmp_img.GetWidth()); x++)
        {
            ApplyTransformation(bmp_img, matrix, x, y);
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}