//
// Created by marta on 26/10/2022.
//
#include "gtest/gtest.h"
#include "../aos/BmpAOS.cpp"
#include "../aos/HistoAOS.cpp"
#include "../aos/MonoAOS.cpp"
#include "../aos/GaussianAOS.cpp"


TEST(TestBalloon, TestCopyAOS){
    BmpAOS bmp;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();

    const std::filesystem::path& file_path=original_path + "\\test\\in_fold\\balloon.bmp";
    const std::filesystem::path& path_out_dir=original_path + "\\test\\out_fold";
    //Leemos una imagen bmp
    bmp.Read(original_path + "\\test\\in_fold\\balloon.bmp");
    //Exportamos la imagen para copiarla y comprobamos que lo exporta correctamente
    int x = bmp.Export(path_out_dir / file_path.filename());
    ASSERT_GE(x,0);
    //Leemos la copia y sacamos los colores de los pixeles
    bmp.Read(original_path + "\\test\\out_fold\\balloon.bmp");
    std::vector<ColorAOS> m_colors_actual = bmp.GetMColors();
    //Leemos el resultado correcto y sacamos los colores de los pixeles
    bmp.Read(original_path + "\\test\\resultados\\copy\\balloon.bmp");
    std::vector<ColorAOS> m_colors_expected = bmp.GetMColors();

    int m_width = bmp.GetWidth();
    int m_height = bmp.GetHeight();
    //Comparamos las imagenes segun los pixeles
    for ( int i = 0; i<m_width*m_height; i++){
        ASSERT_EQ(m_colors_actual[i].r,m_colors_expected[i].r);
        ASSERT_EQ(m_colors_actual[i].g,m_colors_expected[i].g);
        ASSERT_EQ(m_colors_actual[i].b,m_colors_expected[i].b);
    }
}

TEST(TestBalloon, TestHistoAOS){

    BmpAOS bmp;
    HistoAOS hs;
    char caracter, caracter2;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    //Leemos una imagen bmp
    bmp.Read(original_path + "\\test\\in_fold\\balloon.bmp");
    //Creamos el histograma de la imagen
    hs.Histogram(bmp, original_path + "\\test\\out_fold\\balloon.hst");
    //Abrimos tanto el histograma de la imagen como el del resultado correcto
    std::fstream archivo(original_path + "\\test\\out_fold\\balloon.hst");
    std::fstream archivo2(original_path + "\\test\\resultados\\histo\\balloon.hst");
    //Los comparamos
    while (archivo.eof() == 0 || archivo2.eof() == 0) {
        caracter = archivo.get();
        caracter2 = archivo2.get();
        ASSERT_EQ(caracter, caracter2);
    }
    archivo.close();
    archivo2.close();
}

TEST(TestBalloon, TestMonoAOS){
    BmpAOS bmp1;
    BmpAOS bmp2;
    int width1, height1, width2, height2;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    const std::filesystem::path& path1 = original_path + "\\test\\in_fold\\balloon.bmp";
    const std::filesystem::path& path2 = original_path +"\\test\\resultados\\mono\\balloon.bmp";
    const std::filesystem::path& path3 = original_path +"\\test\\out_fold";
    //Leemos la imagen y la transformamos a escala de grises
    bmp1.Read(path1);
    MonoAOS(bmp1);
    //Leemos el resultado
    bmp2.Read(path2);

    width1 = bmp1.GetWidth();
    height1 = bmp1.GetHeight();
    width2 = bmp2.GetWidth();
    height2= bmp2.GetHeight();

    ASSERT_EQ(width2,width1)<< "FAIL";
    ASSERT_EQ(height2,height1)<< "FAIL";
    //Sacamos los colores de los pixeles de ambas
    std::vector<ColorAOS>&m_colors1 = bmp1.GetMColors();
    std::vector<ColorAOS>&m_colors2 = bmp2.GetMColors();
    //Las comparamos segun los colores de los pixeles
    for (int i=0; i<= width2*height2 -1; i++){
        ASSERT_EQ(m_colors2[i].r,m_colors1[i].r)<< "FAIL";
        ASSERT_EQ(m_colors2[i].g,m_colors1[i].g)<< "FAIL";
        ASSERT_EQ(m_colors2[i].b,m_colors1[i].b)<< "FAIL";
    }
}

TEST(TestBalloon, TestGaussAOS){
    BmpAOS bmp1;
    BmpAOS bmp2;
    int width1, height1, width2, height2;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    const std::filesystem::path& path1 = original_path + "\\test\\in_fold\\balloon.bmp";
    const std::filesystem::path& path2 = original_path + "\\test\\resultados\\gauss\\balloon.bmp";
    const std::filesystem::path& path3 = original_path + "\\test\\out_fold";
    //Leemos la imagen y realizamos una tranformacion gaussiana
    bmp1.Read(path1);
    GaussianTransformation(bmp1);
    //Leemos el resultado
    bmp2.Read(path2);

    width1 = bmp1.GetWidth();
    height1 = bmp1.GetHeight();
    width2 = bmp2.GetWidth();
    height2= bmp2.GetHeight();

    ASSERT_EQ(width2,width1);
    ASSERT_EQ(height2,height1);
    //Sacamos los colores de los pixeles de ambas
    std::vector<ColorAOS>&m_colors1 = bmp1.GetMColors();
    std::vector<ColorAOS>&m_colors2 = bmp2.GetMColors();
    //Las comparamos segun los colores de los pixeles
    for (int i=0; i<= width2*height2 ; i++){
        ASSERT_EQ(m_colors2[i].r,m_colors1[i].r);
        ASSERT_EQ(m_colors2[i].g,m_colors1[i].g);
        ASSERT_EQ(m_colors2[i].b,m_colors1[i].b);
    }
}

TEST(TestImagen, IncorrectoBmpAOS){
    BmpAOS bmp;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    //Comprobamos que da error
    int error = bmp.Read( original_path + "\\test\\in_fold\\incorrectoBmp.bmp");
    ASSERT_EQ(error,-1);
}

TEST(TestImagen, IncorrectoFormatoAOS){
    BmpAOS bmp;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    //Comprobamos que da error
    int error = bmp.Read( original_path + "\\test\\in_fold\\incorrecto_formato.jpg");
    ASSERT_EQ(error,-1);
}