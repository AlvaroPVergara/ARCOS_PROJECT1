cmake_minimum_required(VERSION 3.23)
project(ARCOS_PROJECT1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

add_library(common common/common.cpp common/progargs.cpp aos/BmpAOS.cpp common/copy.cpp aos/GaussianAOS.cpp)


add_library(aos aos/BmpAOS.cpp includes/BmpSOA.h aos/HistoAOS.cpp aos/MonoAOS.cpp aos/GaussianAOS.cpp aos/imageaos.cpp common/copy.cpp)
add_library(soa soa/BmpSOA.cpp includes/BmpSOA.h soa/HistoSOA.cpp soa/MonoSOA.cpp soa/GaussianSOA.cpp soa/imagesoa.cpp common/copy.cpp)

add_executable(imgaos aos/imgaos.cpp)
target_link_libraries(imgaos common aos)

add_executable(imgsoa soa/imgsoa.cpp)
target_link_libraries(imgsoa common soa)