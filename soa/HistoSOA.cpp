//
// Created by jmjon on 17/10/2022.
//

#include "../includes/common.h"
#include "../includes/HistoSOA.h"

/*WriteHistogram gets the number of times each color appears with the stucture of arrays n_colors
 * and print it on a txt file*/
void HistoSOA::WriteHistogram(std::string filename)
{
    //We open only to write on it
    std::ofstream outfile;

    //We check if the file has been opened correctly
    outfile.open(filename, std::ios_base::out);
    if (!outfile.is_open()){
        std::cerr << "Error opening new txt file"<< std::endl;
    }

    /*We write each color next to the number of times it is repeated,
     * first one channel completed and then the next one*/
    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors.r[i]<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors.g[i]<<std::endl;
    }

    for ( int i = 0; i<=255; i++){
        outfile<<i<<":"<<n_colors.b[i]<<std::endl;
    }
}

void HistoSOA::CountColors()
{
    int r,g,b;

    /*We read the color of each pixel one by one and count it in that position of the channel in n_colors
       *for example, the count of the color 255 of r chanel is saved on n_colors.r[255]
       * this is repeated for each channel*/
    for ( int i = 0; i<m_width*m_height; i++){
        r = m_colors.redChannel[i];
        n_colors.r[r] += 1;

        g = m_colors.greenChannel[i];
        n_colors.g[g] += 1;

        b = m_colors.blueChannel[i];
        n_colors.b[b] += 1;
    }
}

int HistoSOA::Histogram(BmpSOA file, std::string filename)
{
    //We get the structure of arrays of the colors and the with and height of the image
    m_colors = file.GetMColors();
    m_width = file.GetWidth();
    m_height = file.GetHeight();

    //Resize each array inside the stucture we use to count the colors
    n_colors.r.resize(256);
    n_colors.b.resize(256);
    n_colors.g.resize(256);

    CountColors();
    WriteHistogram(filename);

    return 0;
}
