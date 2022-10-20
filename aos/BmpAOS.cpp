//
// Created by xxmid on 16/10/2022.
//

#include "../includes/BmpAOS.h"

ColorAOS::ColorAOS()
    : r(0), g(0), b(0)
{
}
ColorAOS::ColorAOS(float r, float g, float b)
    :r(r), g(g), b(b)
{
}
ColorAOS::~ColorAOS() = default;
BmpAOS::BmpAOS() = default;
BmpAOS::BmpAOS(int width, int height)
    : m_width(width), m_height(height), m_colors(std::vector<ColorAOS>(width * height))
{
}
BmpAOS::~BmpAOS() = default;

ColorAOS
BmpAOS::GetColor(int x, int y) const {
    return (m_colors[y * m_width + x]);
}

void
BmpAOS::SetColor(const ColorAOS &color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

int
BmpAOS::Read(const std::filesystem::path& path) {
    std::ifstream file;
    file.open(path.generic_string(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal on-read: File opening failed after existence check" << std::endl;
        return (-1);
    }
    // TODO: OPTIMIZATION leer una sola vez todo el header
    unsigned char fileHeader[fileHeaderSize];
    file.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    unsigned char informationHeader[informationHeaderSize];
    file.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);
    // TODO: PARSER y CHECKER el header
    if (ValidateHeader(fileHeader, informationHeader) < 0) {
        file.close();
        return (-1);
    }
    populateColors(file, informationHeader);
    file.close();
    // TODO: Maybe eliminar esto
    std::cout << "File leido!" << std::endl;
    return (0);
}

void
BmpAOS::populateColors(std::ifstream &file, const unsigned char *informationHeader) {
    // TODO: should work with filesize;
    // int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);
    m_colors.resize(m_width * m_height);
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);
    // TODO: OPTIMIZATION leer toda la fila entera con el width/size o todo el archivo directamente y trabajar sobre la ram.
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned  char color[3];
            file.read(reinterpret_cast<char *>(color), 3);
            m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x].g = static_cast<float>(color[1]) / 255.0f;
            m_colors[y * m_width + x].b = static_cast<float>(color[0]) / 255.0f;
        }
        file.ignore(paddingAmount);
    }
}

int
BmpAOS::ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader) {
    //TODO: ELIMINA ESTO
    std::cout << informationHeader << std::endl;
    // TODO: PARSER y CHECKER el header
    if (fileHeader[0] != 'B' || fileHeader[1] != 'M'){
        std::cerr << "El archivo no es un bitmap!" << std::endl;
        return (-1);
    }
    return (0);
}

int BmpAOS::Export(const std::filesystem::path& path) {
    std::ofstream file;
    file.open(path.generic_string(), std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal: File opening failed after existence check" << std::endl;
        return (-1);
    }
    unsigned char bmpPad[3] = { 0, 0, 0};
    const int paddingAmmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmmount * m_width;

    std::vector<char>fileHeader (fileHeaderSize, 0);
    std::vector<char>informationHeader (fileHeaderSize, 0);


    //File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    //File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;

    // Header size
    informationHeader[0] = informationHeaderSize;

    // width
    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;

    // height
    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;

    // planes
    informationHeader[12] = 1;

    // bpp
    informationHeader[14] = 24;
    file.write(reinterpret_cast<char *>(fileHeader.data()), fileHeaderSize);
    file.write(reinterpret_cast<char *>(informationHeader.data()), informationHeaderSize);

    for (int y = 0; y < m_height; y++){
        for (int x = 0; x < m_width; x++){
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

            unsigned char color[] = { b, g, r};

            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char *>(bmpPad), paddingAmmount);
    }
    file.close();
    std::cout << "File created" << std::endl;
    return (0);
}

