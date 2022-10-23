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
    void ResizeMembers(int size);
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
    int Read(const char *path);
    int Export(const std::filesystem::path& path) const;
private:
    u_int m_width{};
    u_int m_height{};
    u_int m_fileSize;
    ColorSOA m_colors;
    int ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader);
    void populateColors(std::ifstream &file, const unsigned char *informationHeader);

    std::vector<u_char> GetColorOnChannels(u_int x, u_int y) const;
};


#endif //ARCOS_PROJECT1_BMPSOA_H
