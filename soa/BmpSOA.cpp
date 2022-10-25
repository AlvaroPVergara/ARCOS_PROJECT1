//
// Created by Joan carlos Naftanaila on 10/17/22.
//

#include "../includes/BmpSOA.h"

/*
 * Our SOA structure, for each instance of the structure we have 3 vectors that hold the information of each color
 * channel of every pixel.
 */

ColorSOA::ColorSOA() = default;
ColorSOA::~ColorSOA() = default;
/*
 * On construction ColorSOA gets the three channels of the file, then stores it on its own.
 */
ColorSOA::ColorSOA(std::vector<u_char> redChanel, std::vector<u_char> greenChanel, std::vector<u_char> blueChannel)
        : redChannel(std::move(redChanel)),
        greenChannel(std::move(greenChanel)),
        blueChannel(std::move(blueChannel))
{
}
/*
 * On call, resizes each of the arrays used to store color channels.
 */
void ColorSOA::ResizeMembers(u_int size) {
    redChannel.resize(size);
    greenChannel.resize(size);
    blueChannel.resize(size);
}

BmpSOA::BmpSOA() = default;
BmpSOA::~BmpSOA() = default;

/*
 * On call populates own members and generates ColorSoa with no significant values.
 */

BmpSOA::BmpSOA(int width, int height)
    : m_width(width), m_height(height), m_colors(
        std::vector<u_char>(width * height),
        std::vector<u_char>(width * height),
        std::vector<u_char>(width * height)
            )
{
}
/*
 * Main read function. We need open the file, check the headers and then fill our Bmp object with the pixel
 * colors on the image.
 * */
int
BmpSOA::Read(const std::filesystem::path& path)
{
    std::ifstream file;
    file.open(path.generic_string(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal: File opening failed after existence check" << std::endl;
        return (-1);
    }
    unsigned char fileHeader[fileHeaderSize];
    file.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    unsigned char informationHeader[informationHeaderSize];
    file.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);
    if (ValidateHeader(fileHeader, informationHeader) < 0) {
        file.close();
        return (-1);
    }
    // We set the read offset to where the data should start.
    int offset = fileHeader[10] + (fileHeader[11] << 8) + (fileHeader[12] << 16) + (fileHeader[13] << 24);
    file.seekg(offset, std::ios_base::beg);
    populateColors(file, informationHeader);
    file.close();
    return (0);
}
/*
 * PopulateColors just reads from the memory the pixel color data and fills the m_colors member with the information
 * for later processing. For sake of simplicity we store just the bytes as they are.
 *
 * SOA: We iterate over each channel array of our m_colors Structure of Arrays and populate each pixel with its information.
 */
void
BmpSOA::populateColors(std::ifstream &file, const unsigned char *informationHeader) {
    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);
    m_colors.ResizeMembers(m_width * m_height);
    const u_int paddingAmount = ((4 - (m_width * 3) % 4) % 4);
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

/*
 * We need to check the header of the bmp in order to ensure we are able to work with the image.
 */

int
BmpSOA::ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader) {
    if (fileHeader[0] != 'B' || fileHeader[1] != 'M'){
        std::cerr << "El archivo no es un bitmap!" << std::endl;
        return (-1);
    }
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

/*
 * Export generates a new file with path address. First we need to generate a correct header with the
 * attributes of our bmp and then dump our color data on the file.
 */

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
    FillHeaders(fileSize, fileHeader, informationHeader);
    file.write(reinterpret_cast<char *>(fileHeader.data()), fileHeaderSize);
    file.write(reinterpret_cast<char *>(informationHeader.data()), informationHeaderSize);
    WriteColors(file, bmpPad, paddingAmmount);
    file.close();
    return (0);
}
/*
 * Given that this is SOA-stored data, we also need to de-encapsulate it:
 * We create a variable-length array with 3 members, the r, g, b values of the pixel.
 * Then we use each SOA channel extracting exactly the pixel info that we need.
 */

void BmpSOA::WriteColors(std::ofstream &file, unsigned char *bmpPad, const u_int paddingAmmount) const {
    for (u_int y = 0; y < m_height; y++) {
        for (u_int x = 0; x < m_width; x++) {
            std::vector<u_char> colors = GetColorOnChannels(x, y);
            unsigned char color[] = {colors[CHAN_B] , colors[CHAN_G], colors[CHAN_R]};

            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char *>(bmpPad), paddingAmmount);
    }
}
/*
 * Helper function to generate the header in memory.
 * We use bit-shift for writing the correct bits of numbers on the memory-bytes.
 */
void BmpSOA::FillHeaders(const u_int fileSize, std::vector<char> &fileHeader,
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

/*
 * GetColorChannels returns a 3 item vector with the data of the pixel requested.
 */
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

