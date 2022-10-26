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
ColorSOA::ColorSOA(std::vector<u_char> red_chanel, std::vector<u_char> green_chanel, std::vector<u_char> blue_channel)
        : redChannel(std::move(red_chanel)),
        greenChannel(std::move(green_chanel)),
        blueChannel(std::move(blue_channel))
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
long long int
BmpSOA::Read(const std::filesystem::path& path)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::ifstream file;
    file.open(path.generic_string(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal: File opening failed after existence check" << std::endl;
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
    // We set the read offset to where the data should start.
    int offset = file_header[10] + (file_header[11] << 8) + (file_header[12] << 16) + (file_header[13] << 24);
    file.seekg(offset, std::ios_base::beg);
    populateColors(file, information_header);
    file.close();
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}

/*
 * PopulateColors just reads from the memory the pixel color data and fills the m_colors member with the information
 * for later processing. For sake of simplicity we store just the bytes as they are.
 *
 * SOA: We iterate over each channel array of our m_colors Structure of Arrays and populate each pixel with its information.
 */
void
BmpSOA::populateColors(std::ifstream &file, const u_char *information_header) {
    m_width = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) + (information_header[7] << 24);
    m_height = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) + (information_header[11] << 24);
    m_colors.ResizeMembers(m_width * m_height);
    const u_int padding_amount = ((4 - (m_width * 3) % 4) % 4);
    for (u_int y = 0; y < m_height; y++) {
        for (u_int x = 0; x < m_width; x++) {
            u_char color[3];
            file.read(reinterpret_cast<char *>(color), 3);
            m_colors.redChannel[y * m_width + x] = color[2];
            m_colors.greenChannel[y * m_width + x] = color[1];
            m_colors.blueChannel[y * m_width + x] = color[0];
        }
        file.ignore(padding_amount);
    }
}

/*
 * We need to check the header of the bmp in order to ensure we are able to work with the image.
 */

int
BmpSOA::ValidateHeader(const u_char *file_header, const u_char *information_header) {
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

long long int
BmpSOA::Export(const std::filesystem::path& path) const {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::ofstream file;
    file.open(path.generic_string(), std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fatal: File opening failed after existence check" << std::endl;
        return (-1);
    }
    u_char bmp_pad[3] = {0, 0, 0};
    const u_int padding_ammount = ((4 - (m_width * 3) % 4) % 4);
    const u_int file_size = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + padding_ammount * m_width;
    std::vector<char>file_header (fileHeaderSize, 0);
    std::vector<char>information_header (informationHeaderSize, 0);
    FillHeaders(file_size, file_header, information_header);
    file.write(reinterpret_cast<char *>(file_header.data()), fileHeaderSize);
    file.write(reinterpret_cast<char *>(information_header.data()), informationHeaderSize);
    WriteColors(file, bmp_pad, padding_ammount);
    file.close();
    auto end_time = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
}
/*
 * Given that this is SOA-stored data, we also need to de-encapsulate it:
 * We create a variable-length array with 3 members, the r, g, b values of the pixel.
 * Then we use each SOA channel extracting exactly the pixel info that we need.
 */

void BmpSOA::WriteColors(std::ofstream &file, u_char *bmp_pad, const u_int padding_ammount) const {
    for (u_int y = 0; y < m_height; y++) {
        for (u_int x = 0; x < m_width; x++) {
            std::vector<u_char> colors = GetColorOnChannels(x, y);
            u_char color[] = {colors[CHAN_B] , colors[CHAN_G], colors[CHAN_R]};

            file.write(reinterpret_cast<char*>(color), 3);
        }
        file.write(reinterpret_cast<char *>(bmp_pad), padding_ammount);
    }
}
/*
 * Helper function to generate the header in memory.
 * We use bit-shift for writing the correct bits of numbers on the memory-bytes.
 */
void BmpSOA::FillHeaders(const u_int file_size, std::vector<char> &file_header,
                         std::vector<char> &information_header) const {//File type
    file_header[0] = 'B';
    file_header[1] = 'M';
    //File size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    // Pixel data offset
    file_header[10] = fileHeaderSize + informationHeaderSize;
    // Header size
    information_header[0] = informationHeaderSize;
    // width
    information_header[4] = m_width;
    information_header[5] = m_width >> 8;
    information_header[6] = m_width >> 16;
    information_header[7] = m_width >> 24;
    // height
    information_header[8] = m_height;
    information_header[9] = m_height >> 8;
    information_header[10] = m_height >> 16;
    information_header[11] = m_height >> 24;
    // planes
    information_header[12] = 1;
    // bpp
    information_header[14] = 24;
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

