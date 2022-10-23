//
// Created by Joan carlos Naftanaila on 10/17/22.
//

// TODO: BmpAOS and BmpSOA share m_height and width members and Read function (maybe write too) and constants, only changes are on populate functionality.


#include <utility>

#include "../includes/BmpSOA.h"

ColorSOA::ColorSOA() = default;
ColorSOA::~ColorSOA() = default;

ColorSOA::ColorSOA(std::vector<u_char> redChanel, std::vector<u_char> greenChanel, std::vector<u_char> blueChannel)
        : redChannel(std::move(redChanel)), greenChannel(std::move(greenChanel)), blueChannel(std::move(blueChannel))
{

}

void ColorSOA::ResizeMembers(int size) {
    redChannel.resize(size);
    greenChannel.resize(size);
    blueChannel.resize(size);
}

BmpSOA::BmpSOA() = default;
BmpSOA::~BmpSOA() = default;

BmpSOA::BmpSOA(int width, int height)
    : m_width(width), m_height(height), m_colors(
        std::vector<u_char>(width * height),
        std::vector<u_char>(width * height),
        std::vector<u_char>(width * height)
            )
{
}

int
BmpSOA::Read(const std::filesystem::path& path)
{
    std::ifstream file;
    file.open(path.generic_string(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal: File opening failed after existence check" << std::endl;
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
    int offset = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12] << 16) + (fileHeader[13] << 24);
    std::cout << "Offset is: " << offset << std::endl;
    file.seekg(offset, std::ios_base::beg);
    populateColors(file, informationHeader);
    file.close();
    // TODO: Maybe eliminar esto
    std::cout << "File leido!" << std::endl;
    return (0);
}

void
BmpSOA::populateColors(std::ifstream &file, const unsigned char *informationHeader) {
    // TODO: should work with filesize;
    // int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);
    m_colors.ResizeMembers(m_width * m_height);
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);
    // TODO: OPTIMIZATION leer toda la fila entera con el width/size o todo el archivo directamente y trabajar sobre la ram.
    for (u_int y = 0; y < m_height; y++) {
        for (u_int x = 0; x < m_width; x++) {
            unsigned  char color[3];
            file.read(reinterpret_cast<char *>(color), 3);
            m_colors.redChannel[y * m_width + x] = color[2];
            m_colors.greenChannel[y * m_width + x] = color[1];
            m_colors.blueChannel[y * m_width + x] = color[0];
        }
        file.ignore(paddingAmount);
    }
}

int
BmpSOA::ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader) {
    // TODO: PARSER y CHECKER el header
    if (fileHeader[0] != 'B' || fileHeader[1] != 'M'){
        std::cerr << "El archivo no es un bitmap!" << std::endl;
        return (-1);
    }
    //TODO: CHECK IF FILESIZE IS CORRECT;
    m_fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);

    int num_plane =  informationHeader[12] + (informationHeader[13] << 8);
    if (num_plane != 1)
    {
        std::cerr << "El numero de planos del archivo es incorrecto!" << std::endl;
        return (-1);
    }
    int pixel_size = informationHeader[14] + (informationHeader[15] << 8);
    if (pixel_size != 24)
    {
        std::cerr << "El tamaño del pixel es incorrecto!" << std::endl;
        return (-1);
    }
    int compression = informationHeader[16] + (informationHeader[17] << 8) + (informationHeader[18] << 16) + (informationHeader[19] << 24);
    if (compression != 0)
    {
        std::cerr << "El archivo contiene compresión, por lo que no puede ser procesado!" << std::endl;
        return (-1);
    }
    return (0);
}

int BmpSOA::Export(const std::filesystem::path& path) const {
    std::ofstream file;
    file.open(path.generic_string(), std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal: File opening failed after existence check" << std::endl;
        return (-1);
    }
    unsigned char bmpPad[3] = { 0, 0, 0};
    const u_int paddingAmmount = ((4 - (m_width * 3) % 4) % 4);

    const u_int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmmount * m_width;

    std::vector<char>fileHeader (fileHeaderSize, 0);
    std::vector<char>informationHeader (informationHeaderSize, 0);


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

    for (u_int y = 0; y < m_height; y++) {
        for (u_int x = 0; x < m_width; x++) {
            std::vector<u_char> colors = GetColorOnChannels(x, y);
            unsigned char color[] = { colors[CHAN_B] , colors[CHAN_G], colors[CHAN_R]};

            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char *>(bmpPad), paddingAmmount);
    }
    file.close();
    std::cout << "File created" << std::endl;
    return (0);
}

std::vector<u_char> BmpSOA::GetColorOnChannels(u_int x, u_int y) const {
    return std::vector<u_char> {
            m_colors.redChannel[x + y * m_width],
            m_colors.greenChannel[x + y * m_width],
            m_colors.blueChannel[x + y * m_width]
    };
}

u_int BmpSOA::GetWidth() {
    return m_width;
}

u_int BmpSOA::GetHeight() {
    return m_height;
}

ColorSOA &BmpSOA::GetMColors() {
    return m_colors;
}

void BmpSOA::SetColor(std::vector<u_char> new_colors, u_int x, u_int y) {
    m_colors.redChannel[x + y * m_width] = new_colors[CHAN_R];
    m_colors.greenChannel[x + y * m_width] = new_colors[CHAN_G];
    m_colors.blueChannel[x + y * m_width] = new_colors[CHAN_B];
}

