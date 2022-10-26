//
// Created by xxmid on 16/10/2022.
//

#include "../includes/BmpAOS.h"
/*
 * Our AOS structure, for each instance of the structure we have 3 bytes to store pixel information.
 */
ColorAOS::ColorAOS()
    : r(0), g(0), b(0)
{
}
ColorAOS::ColorAOS(u_char r, u_char g, u_char b)
    :r(r), g(g), b(b)
{
}
ColorAOS::~ColorAOS() = default;
BmpAOS::BmpAOS() = default;
/*
 * On construction, we resize our Array of Structures.
 */

BmpAOS::BmpAOS(u_int width, u_int height)
    : m_width(width), m_height(height), m_colors(std::vector<ColorAOS>(width * height))
{
}
BmpAOS::~BmpAOS() = default;

/*
 * Gets a specific pixel information
 */
ColorAOS
BmpAOS::GetColor(u_int x, u_int y) const {
    return (m_colors[y * m_width + x]);
}

/*
 * Sets a specific pixel information
 */
void
BmpAOS::SetColor(const ColorAOS &color, u_int x, u_int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

/*
 * Main read function. We need open the file, check the headers and then fill our Bmp object with the pixel
 * colors on the image.
 * */
int
BmpAOS::Read(const std::filesystem::path& path) {
    std::ifstream file;
    file.open(path.generic_string(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal on-read: File opening failed after existence check" << std::endl;
        return (-1);
    }
    u_char file_header[fileHeaderSize];
    file.read(reinterpret_cast<char*>(file_header), fileHeaderSize);
    u_char information_header[informationHeaderSize];
    file.read(reinterpret_cast<char*>(information_header), informationHeaderSize);
    if (ValidateHeader(file_header, information_header) < 0) {
        file.close();
        return (-1);
    }
    int offset = file_header[10] + (file_header[11] << 8) + (file_header[12] << 16) + (file_header[13] << 24);
    // We set the read offset to where the data should start.
    file.seekg(offset, std::ios_base::beg);
    PopulateColors(file, information_header);
    file.close();
    return (0);
}

/*
 * PopulateColors just reads from the memory the pixel color data and fills the m_colors member with the information
 * for later processing. For sake of simplicity we store just the bytes as they are.
 *
 * AOS: We iterate over our m_colors Array Of Structurs and populate each pixel with its information.
 */
void
BmpAOS::PopulateColors(std::ifstream &file, const u_char *information_header) {
    m_width = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) + (information_header[7] << 24);
    m_height = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) + (information_header[11] << 24);
    m_colors.resize(m_width * m_height);
    const u_int padding_amount = ((4 - (m_width * 3) % 4) % 4);
    for (u_int y = 0; y < m_height; y++) {
        for (u_int x = 0; x < m_width; x++) {
            unsigned  char color[3];
            file.read(reinterpret_cast<char *>(color), 3);
            m_colors[y * m_width + x].r = color[2];
            m_colors[y * m_width + x].g = color[1];
            m_colors[y * m_width + x].b = color[0];
        }
        file.ignore(padding_amount);
    }
}

/*
 * We need to check the header of the bmp in order to ensure we are able to work with the image.
 */

int
BmpAOS::ValidateHeader(const u_char *file_header, const u_char *information_header) {
    if (file_header[0] != 'B' || file_header[1] != 'M'){
        std::cerr << "El archivo no es un bitmap!" << std::endl;
        return (-1);
    }
    int num_plane = information_header[12] + (information_header[13] << 8);
    if (num_plane != 1)
    {
        std::cerr << "El numero de planos del archivo es incorrecto!" << std::endl;
        return (-1);
    }
    int pixel_size = information_header[14] + (information_header[15] << 8);
    if (pixel_size != 24)
    {
        std::cerr << "El tamaño del pixel es incorrecto!" << std::endl;
        return (-1);
    }
    int compression = information_header[16] + (information_header[17] << 8) + (information_header[18] << 16) + (information_header[19] << 24);
    if (compression != 0)
    {
        std::cerr << "El archivo contiene compresión, por lo que no puede ser procesado!" << std::endl;
        return (-1);
    }
    return (0);
}

/*
 * Export generates a new file with path address. First we need to generate a correct header with the
 * attributes of our bmp and then dump our color data on the file.
 */

int BmpAOS::Export(const std::filesystem::path& path) const {
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
    FillHeader(fileSize, fileHeader, informationHeader);
    file.write(reinterpret_cast<char *>(fileHeader.data()), fileHeaderSize);
    file.write(reinterpret_cast<char *>(informationHeader.data()), informationHeaderSize);
    WriteColors(file, bmpPad, paddingAmmount);
    file.close();
    return (0);
}

/*
 * Given that this is AOS-stored data, we need to de-encapsulate it:
 * We create a variable-length array with 3 members, the r, g, b values of the pixel.
 * Then we use that VLA to write to memory.
 * Note that we are using byte arrays only when we need a buffer for writing.
 */

void BmpAOS::WriteColors(std::ofstream &file, unsigned char *bmpPad, const u_int paddingAmmount) const {
    for (u_int y = 0; y < m_height; y++) {
        for (u_int x = 0; x < m_width; x++) {
            unsigned char color[] = {
                    GetColor(x, y).b,
                    GetColor(x, y).g,
                    GetColor(x, y).r
            };
            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char *>(bmpPad), paddingAmmount);
    }
}

/*
 * Helper function to generate the header in memory.
 * We use bit-shift for writing the correct bits of numbers on the memory-bytes.
 */

void BmpAOS::FillHeader(const u_int fileSize, std::vector<char> &fileHeader,
                        std::vector<char> &informationHeader) const {//File type
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
}

/*
 * Getters for members.
 */

u_int BmpAOS::GetWidth() const {
    return m_width;
}

u_int BmpAOS::GetHeight() const {
    return m_height;
}

std::vector<ColorAOS> &BmpAOS::GetMColors() {
    return m_colors;
}