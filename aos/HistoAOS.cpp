//
// Created by jmjon on 17/10/2022.
//

#include "../includes/common.h"
#include "../includes/BmpAOS.h"
#include "../includes/HistoAOS.h"

//WriteHistogram gets the number of times each color appears with the array of stuctures n_colors and print it on a txt file
void HistoAOS::WriteHistogram(std::string filename)
{
    //We open only to write on it
    std::ofstream outfile;
    outfile.open(filename, std::ios_base::out);

    //We check if the file has been opened correctly
    if (!outfile.is_open()){
        std::cerr << "Error opening new txt file"<< std::endl;
    }

    /*We write each color next to the number of times it is repeated,
     * first one channel completed and then the next one*/
    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors[i].r<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors[i].g<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors[i].b<<std::endl;
    }
}

void HistoAOS::CountColors()
{
    int r,g,b;

    /*We read the color of each pixel one by one and count it in that position of n_colors
     *for example, the count of the color 255 is saved on n_colors[255]
     * this is repeated for each channel*/
    for ( int i = 0; i<m_width*m_height; i++){

        r = m_colors[i].r;
        n_colors[r].r += 1;

        g = m_colors[i].g;
        n_colors[g].g += 1;

        b = m_colors[i].b;
        n_colors[b].b += 1;
    }
}

int HistoAOS::Histogram(BmpAOS file, std::string filename)
{
    //We get the array of structures of the colors and the with and height of the image
    m_colors = file.GetMColors();
    m_width = file.GetWidth();
    m_height = file.GetHeight();

    //Resize the array where is going to be the structures we use to count the colors
    n_colors.resize(256);

    CountColors();
    WriteHistogram(filename);

    return 0;
}

