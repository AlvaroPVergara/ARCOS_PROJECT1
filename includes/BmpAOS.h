//
// Created by xxmid on 16/10/2022.
//

#ifndef ARCOS_PROJECT1_BMPAOS_H
#define ARCOS_PROJECT1_BMPAOS_H

#include "common.h"

struct ColorAOS {
    u_char r, g, b;
    ColorAOS();
    ColorAOS(u_char r, u_char g, u_char b);
    ~ColorAOS();
};

class BmpAOS {
public:
    BmpAOS();
    BmpAOS(u_int width, u_int height);
    ~BmpAOS();
    [[nodiscard]] ColorAOS GetColor(u_int x, u_int y) const;
    void SetColor(const ColorAOS& color, u_int x, u_int y);
    static const u_int fileHeaderSize = 14;
    static const u_int informationHeaderSize = 40;
    int Read(const std::filesystem::path& path);
    [[nodiscard]] int Export(const std::filesystem::path& path) const;
    [[nodiscard]] u_int GetWidth() const;
    [[nodiscard]] u_int GetHeight() const;
    std::vector<ColorAOS> &GetMColors() ;
private:
    u_int m_width{};
    u_int m_height{};
    std::vector<ColorAOS> m_colors;
    static int ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader);
    void populateColors(std::ifstream &file, const unsigned char *informationHeader);
};

#endif //ARCOS_PROJECT1_BMPAOS_H
