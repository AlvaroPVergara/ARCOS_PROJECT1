//
// Created by xxmid on 16/10/2022.
//

#ifndef ARCOS_PROJECT1_BMPAOS_H
#define ARCOS_PROJECT1_BMPAOS_H

#include "common.h"

struct ColorAOS {
    float r, g, b;
    ColorAOS();
    ColorAOS(float r, float g, float b);
    ~ColorAOS();
};

class BmpAOS {
public:
    BmpAOS();
    BmpAOS(int width, int height);
    ~BmpAOS();
    [[nodiscard]] ColorAOS GetColor(int x, int y) const;
    void SetColor(const ColorAOS& color, int x, int y);
    static const int fileHeaderSize = 14;
    static const int informationHeaderSize = 40;
    int Read(const std::filesystem::path& path);
    int Export(const std::filesystem::path& path);
private:
    int m_width{};
    int m_height{};
    std::vector<ColorAOS> m_colors;
    static int ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader);
    void populateColors(std::ifstream &file, const unsigned char *informationHeader);
};

#endif //ARCOS_PROJECT1_BMPAOS_H
