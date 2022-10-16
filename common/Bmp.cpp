//
// Created by xxmid on 16/10/2022.
//

#include "../includes/Bmp.h"

Color::Color()
    : r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b)
    :r(r), g(g), b(b)
{
}

Color::~Color() {
}

Bmp::Bmp() {
}

Bmp::Bmp(int width, int height)
    : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height))
{
}


Bmp::~Bmp() {
}

Color Bmp::GetColor(int x, int y) const {
    return (m_colors[y * m_width + x]);
}

void Bmp::SetColor(const Color &color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

int Bmp::Read(const char *path) {
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Fatal: File opening failed after existence check" << std::endl;
        return (-1);
    }
    // TODO: OPTIMIZATION leer una sola vez todo el header
    unsigned char fileHeader[fileHeaderSize];
    file.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    unsigned char informationHeader[informationHeaderSize];
    file.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);
    // TODO: PARSER y CHECKER el header
    if (ValidateHeader(fileHeader, informationHeader) < 0)
    {
        file.close();
        return (-1);
    }
    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    m_colors.resize(m_width * m_height);

    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);


    // TODO: OPTIMIZATION leer toda la fila entera con el width/size o todo el archivo directamente y trabajar sobre la ram.
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned  char color[3];
            file.read(reinterpret_cast<char *>(color), 3);
            m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x].g = static_cast<float>(color[1]) / 255.0f;
            m_colors[y * m_width + x].b = static_cast<float>(color[3]) / 255.0f;
        }

        file.ignore(paddingAmount);
    }

    file.close();
    // TODO: Maybe eliminar esto
    std::cout << "File leido!" << std::endl;
    return (0);
}

int Bmp::ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader) {
    //TODO: ELIMINA ESTO
    std::cout << informationHeader << std::endl;
    // TODO: PARSER y CHECKER el header
    if (fileHeader[0] != 'B' || fileHeader[1] != 'M'){
        std::cerr << "El archivo no es un bitmap!" << std::endl;
        return (-1);
    }
    return (0);
}

