//
// Created by marta on 26/10/2022.
//
#include "gtest/gtest.h"
#include "../common/common.cpp"
//Funcion main que ejecuta todos los test
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}