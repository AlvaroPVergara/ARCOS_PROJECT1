//
// Created by xxmid on 16/10/2022.
//

#ifndef ARCOS_PROJECT1_BMP_H
#define ARCOS_PROJECT1_BMP_H

#include "common.h"

struct Color {
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Bmp {
public:
    Bmp();
    Bmp(int width, int height);
    ~Bmp();

    [[nodiscard]] Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    static const int fileHeaderSize = 14;
    static const int informationHeaderSize = 40;

    int Read(const char *path);
private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;

    int ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader);
};


#endif //ARCOS_PROJECT1_BMP_H
