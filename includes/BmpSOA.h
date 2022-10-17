//
// Created by Joan carlos Naftanaila on 10/17/22.
//

#ifndef ARCOS_PROJECT1_BMPSOA_H
#define ARCOS_PROJECT1_BMPSOA_H

#include "common.h"

struct ColorSOA {
    std::vector<char> redChannel;
    std::vector<char> greenChannel;
    std::vector<char> blueChannel;
    ColorSOA();
    ColorSOA(std::vector<char> redChanel, std::vector<char> greenChanel, std::vector<char> blueChannel);
    ~ColorSOA();
    void ResizeMembers(int size);
};

class BmpSOA {
public:
    BmpSOA();
    BmpSOA(int width, int height);
    ~BmpSOA();
    static const int fileHeaderSize = 14;
    static const int informationHeaderSize = 40;
    int Read(const char *path);
private:
    int m_width{};
    int m_height{};
    ColorSOA m_colors;
    static int ValidateHeader(const unsigned char *fileHeader, const unsigned char *informationHeader);
    void populateColors(std::ifstream &file, const unsigned char *informationHeader);
};


#endif //ARCOS_PROJECT1_BMPSOA_H
