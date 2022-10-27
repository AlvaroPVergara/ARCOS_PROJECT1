//
// Created by middiz on 20/10/22.
//

#include "../includes/common.h"
#include "../includes/BmpAOS.h"

struct DoubleColorAOS {
    DoubleColorAOS(double r, double g, double b);
    DoubleColorAOS();
    double r;
    double g;
    double b;
};
DoubleColorAOS::DoubleColorAOS(double r, double g, double b)
    : r(r), g(g), b(b)
{
}

DoubleColorAOS::DoubleColorAOS()
        : r(0), g(0), b(0){

}

std::vector<DoubleColorAOS> normalizeBmp(BmpAOS &aos);

void
ApplyTransformation(BmpAOS& bmp_img, std::vector<DoubleColorAOS> &matrix_normalized, const std::vector<std::vector<double>> &matrix_mascara, std::vector<int>coords)
{
    double result[3] = {0.0f, 0.0f, 0.0f};
    DoubleColorAOS buff_pixel(0,0,0);

    int x = coords[0];
    int y = coords[1];
    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {
            buff_pixel = ((x + i >= 0) && (y + j >= 0) && ((x + i) < static_cast<int>(bmp_img.GetWidth())) && ((y + j) < static_cast<int>(bmp_img.GetHeight()))) ? matrix_normalized[x + y * bmp_img.GetWidth()] : DoubleColorAOS(0, 0, 0);

            result[0] += matrix_mascara[i + 2][j + 2] * buff_pixel.r;
            result[1] += matrix_mascara[i + 2][j + 2] * buff_pixel.g;
            result[2] += matrix_mascara[i + 2][j + 2] * buff_pixel.b;
        }
    }
    double append[3] = {result[0], result[1], result[2]};
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    bmp_img.SetColor(ColorAOS(static_cast<unsigned char>((append[0] / 273.0f) * 255.0f),
                              static_cast<unsigned char>((append[1] / 273.0f) * 255.0f),
                              static_cast<unsigned char>((append[2] / 273.0f) * 255.0f)
                                    ), x, y);
}

long long int
GaussianTransformation(BmpAOS& bmp_img)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    const std::vector<std::vector<double>> matrix_mascara = {
            {1.0f,4.0f,7.0f,4.0f,1.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {7.0f,26.0f,41.0f,26.0f,7.0f},
            {4.0f,16.0f,26.0f,16.0f,4.0f},
            {1.0f,4.0f,7.0f,4.0f,1.0f}
    };
    std::vector<DoubleColorAOS> matrix_normalized = normalizeBmp(bmp_img);
    for (int y = 0; y < static_cast<int>(bmp_img.GetHeight()); y++)
    {
        for (int x = 0; x < static_cast<int>(bmp_img.GetWidth()); x++)
        {
            ApplyTransformation(bmp_img, matrix_normalized, matrix_mascara, std::vector<int>{x, y});
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}



std::vector<DoubleColorAOS> normalizeBmp(BmpAOS &aos) {
    std::vector<DoubleColorAOS> normalized_matrix;
    normalized_matrix.resize(aos.GetWidth() * aos.GetHeight());
    for (int y = 0; y < static_cast<int>(aos.GetHeight()); y++)
    {
        for (int x = 0; x < static_cast<int>(aos.GetWidth()); x++)
        {
            ColorAOS pixel = aos.GetColor(x,y);
            normalized_matrix[x + y * aos.GetWidth()].r = static_cast<float>(pixel.r) / 255.0f;
            normalized_matrix[x + y * aos.GetWidth()].g = static_cast<float>(pixel.g) / 255.0f;
            normalized_matrix[x + y * aos.GetWidth()].b = static_cast<float>(pixel.b) / 255.0f;
        }
    }
    return (normalized_matrix);
}
