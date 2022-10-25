//
// Created by Joan carlos Naftanaila on 10/17/22.
//

#ifndef ARCOS_PROJECT1_BMPSOA_H
#define ARCOS_PROJECT1_BMPSOA_H

#include "common.h"

struct ColorSOA {
    std::vector<u_char> redChannel;
    std::vector<u_char> greenChannel;
    std::vector<u_char> blueChannel;
    ColorSOA();
    ColorSOA(std::vector<u_char> redChanel, std::vector<u_char> greenChanel, std::vector<u_char> blueChannel);
    ~ColorSOA();
    void ResizeMembers(u_int size);
};

class BmpSOA {
public:
    const short CHAN_R = 0;
    const short CHAN_G = 1;
    const short CHAN_B = 2;
    BmpSOA();
    BmpSOA(int width, int height);
    ~BmpSOA();
    static const int fileHeaderSize = 14;
    static const int informationHeaderSize = 40;
    int Read(const std::filesystem::path& path);
    int Export(const std::filesystem::path& path) const;
    u_int GetWidth();
    u_int GetHeight();
    ColorSOA &GetMColors();
    [[nodiscard]] std::vector<u_char> GetColorOnChannels(u_int x, u_int y) const;
    void SetColor(std::vector<u_char> new_colors, u_int x, u_int y);
private:
    u_int m_width{};
    u_int m_height{};
    u_int m_fileSize;
    ColorSOA m_colors;
    int ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader);
    void populateColors(std::ifstream &file, const unsigned char *informationHeader);


    void FillHeaders(const u_int fileSize, std::vector<char> &fileHeader, std::vector<char> &informationHeader) const;

    void WriteColors(std::ofstream &file, unsigned char *bmpPad, const u_int paddingAmmount) const;
};


#endif //ARCOS_PROJECT1_BMPSOA_H
