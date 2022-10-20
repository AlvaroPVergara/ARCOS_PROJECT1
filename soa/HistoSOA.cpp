//
// Created by jmjon on 17/10/2022.
//

#include "../includes/common.h"
#include "../includes/HistoSOA.h"

void HistoSOA::write(std::string filename)
{
    std::fstream outfile;
    outfile.open(filename, std::ios_base::out);

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

void HistoSOA::count_colors()
{
    int r,g,b;

    for ( int i = 0; i<m_width*m_height; i++){
        r = m_colors.redChannel[i] * 255.0f;
        n_colors.r[r] += 1;

        g = m_colors.greenChannel[i] * 255.0f;
        n_colors.g[g] += 1;

        b = m_colors.blueChannel[i] * 255.0f;
        n_colors.b[b] += 1;
    }
}

int HistoSOA::histogram(BmpSOA file, std::string filename)
{
    m_colors = file.getM_color();
    m_width = file.getM_width();
    m_height = file.getM_height();

    n_colors.r.resize(256);
    n_colors.b.resize(256);
    n_colors.g.resize(256);

    count_colors();
    write(filename);

    return 0;
}

/*
{
 void Histograma(BmpSOA archivo )
{
    int r,g,b,m_width,m_height;

    ColorSOA m_colors;
    N_Colors n_colors;

    m_colors = archivo.getM_color();
    m_width = archivo.getM_width();
    m_height = archivo.getM_height();

    n_colors.r.resize(256);
    n_colors.b.resize(256);
    n_colors.g.resize(256);


    for ( int i = 0; i<=m_width*m_height; i++){

            r = m_colors.redChannel[i] * 255.0f;
            n_colors.r[r] += 1;

            g = m_colors.greenChannel[i] * 255.0f;
            n_colors.g[g] += 1;

            b = m_colors.blueChannel[i] * 255.0f;
            n_colors.b[b] += 1;

    }

    std::string filename2("C:\\Users\\jmjon\\CLionProjects\\ARCOS_PROJECT1\\test\\out\\HistoSOA.hst");
    std::fstream outfile;

    outfile.open(filename2, std::ios_base::out);

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



    ColorAOS a;
    a = archivo.GetColor(100,100);
    std::string text( "%d:Some huge text to write to\n");
    std::string filename2("C:\\Users\\jmjon\\CLionProjects\\ARCOS_PROJECT1\\test\\out\\tmp2.hst");
    std::fstream outfile;

    outfile.open(filename2, std::ios_base::out);
    outfile<<a.r;

    return EXIT_SUCCESS;

}



    ColorAOS a;
    a = archivo.GetColor(100,100);
    std::cout<<a.r<<std::endl;
    std::cout<<a.b<<std::endl;
    std::cout<<a.g<<std::endl;
    return 0;


        ColorAOS a;
    a = archivo.GetColor(100,100);
    std::string text("Some huge text to write to\n");
    std::string filename2("C:\\Users\\jmjon\\CLionProjects\\ARCOS_PROJECT1\\test\\out\\tmp2.hst");
    std::fstream outfile;

    outfile.open(filename2, std::ios_base::out);
    if (!outfile.is_open()) {
        std::cout << "failed to open " << filename2 << '\n';
    } else {
        outfile.write(text.data(), text.size());
        outfile.write(text.data(), text.size());
        std::cout << "Done Writing!" << std::endl;
    }

    return EXIT_SUCCESS;
 */


/*
 {
    std::vector<N_Colors> n_colors;
    n_colors.resize(256);
    int r,g,b,m_width,m_height;
    std::vector<ColorAOS> m_colors;
    m_colors = archivo.getM_color();
    m_width = archivo.getM_width();
    m_height = archivo.getM_height();

    for ( int i = 0; i<=m_width; i++){
        for ( int j = 0; j<=m_height; j++){
            r = m_colors[i*j].r * 255.0f;
            n_colors[r].r += 1;
            g = m_colors[i*j].g * 255.0f;
            n_colors[g].g += 1;
            b = m_colors[i*j].b * 255.0f;
            n_colors[b].b += 1;

        }
    }

    std::cout<<n_colors[255].r<<std::endl;
    std::cout<<m_width<<std::endl;
    std::cout<<m_height<<std::endl;





    return 0;
}



 */