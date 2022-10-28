//
// Created by jmjon on 28/10/2022.
//
#include "gtest/gtest.h"
#include "../soa/BmpSOA.cpp"
#include "../soa/HistoSOA.cpp"
#include "../soa/MonoSOA.cpp"
#include "../soa/GaussianSOA.cpp"

TEST(TestBalloon, TestCopySOA){
    BmpSOA bmp;
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
    ColorSOA m_colors_actual = bmp.GetMColors();
    //Leemos el resultado correcto y sacamos los colores de los pixeles
    bmp.Read(original_path + "\\test\\resultados\\copy\\balloon.bmp");
    ColorSOA m_colors_expected = bmp.GetMColors();

    int m_width = bmp.GetWidth();
    int m_height = bmp.GetHeight();
    //Comparamos las imagenes segun los pixeles
    for ( int i = 0; i<m_width*m_height; i++){
        ASSERT_EQ(m_colors_actual.redChannel[i],m_colors_expected.redChannel[i]);
        ASSERT_EQ(m_colors_actual.greenChannel[i],m_colors_expected.greenChannel[i]);
        ASSERT_EQ(m_colors_actual.blueChannel[i],m_colors_expected.blueChannel[i]);
    }
}

TEST(TestBalloon, TestHistoSOA){

    BmpSOA bmp;
    HistoSOA hs;
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
    while (archivo.eof() == 0 ||archivo2.eof() == 0) {
        caracter = archivo.get();
        caracter2 = archivo2.get();
        ASSERT_EQ(caracter, caracter2);
    }
    archivo.close();
    archivo2.close();
}

TEST(TestBalloon, TestMonoSOA){
    BmpSOA bmp1;
    BmpSOA bmp2;
    int width1, height1, width2, height2;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    const std::filesystem::path& path1 = original_path + "\\test\\in_fold\\balloon.bmp";
    const std::filesystem::path& path2 = original_path +"\\test\\resultados\\mono\\balloon.bmp";
    const std::filesystem::path& path3 = original_path +"\\test\\out_fold";
    //Leemos la imagen y la transformamos a escala de grises
    bmp1.Read(path1);
    MonoSOA(bmp1);
    //Leemos el resultado
    bmp2.Read(path2);

    width1 = bmp1.GetWidth();
    height1 = bmp1.GetHeight();
    width2 = bmp2.GetWidth();
    height2= bmp2.GetHeight();

    ASSERT_EQ(width2,width1);
    ASSERT_EQ(height2,height1);
    //Sacamos los colores de los pixeles de ambas
    ColorSOA& m_colors1 = bmp1.GetMColors();
    ColorSOA& m_colors2 = bmp2.GetMColors();
    //Las comparamos segun los colores de los pixeles
    for (int i=0; i<= width2*height2 -1; i++){
        ASSERT_EQ(m_colors2.redChannel[i],m_colors1.redChannel[i]);
        ASSERT_EQ(m_colors2.greenChannel[i],m_colors1.greenChannel[i]);
        ASSERT_EQ(m_colors2.blueChannel[i],m_colors1.blueChannel[i]);
    }
}
TEST(TestBalloon, TestGaussSOA){
    BmpSOA bmp1;
    BmpSOA bmp2;
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
    ColorSOA& m_colors1 = bmp1.GetMColors();
    ColorSOA& m_colors2 = bmp2.GetMColors();
    //Las comparamos segun los colores de los pixeles
    for (int i=0; i<= width2*height2 -1; i++){
        ASSERT_EQ(m_colors2.redChannel[i],m_colors1.redChannel[i]);
        ASSERT_EQ(m_colors2.greenChannel[i],m_colors1.greenChannel[i]);
        ASSERT_EQ(m_colors2.blueChannel[i],m_colors1.blueChannel[i]);
    }
}

TEST(TestImagen, IncorrectoBmpSOA){
    BmpSOA bmp;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    //Comprobamos que da error
    int error = bmp.Read( original_path + "\\test\\in_fold\\incorrectoBmp.bmp");
    ASSERT_EQ(error,-1);
}

TEST(TestImagen, IncorrectoFormatoSOA){
    BmpSOA bmp;
    //Generamos un path general para todos los ordenadores
    std::string original_path=std::filesystem::current_path().remove_filename().parent_path().remove_filename().generic_string();
    //Comprobamos que da error
    int error = bmp.Read( original_path + "\\test\\in_fold\\incorrecto_formato.jpg");
    ASSERT_EQ(error,-1);
}