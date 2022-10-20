cmake_minimum_required(VERSION 3.20)
project(ARCOS_PROJECT1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

add_library(common common/common.cpp common/parser.cpp aos/BmpAOS.cpp common/copy.cpp common/gaussian.cpp)


add_library(aos aos/BmpAOS.cpp includes/BmpSOA.h)
add_library(soa soa/BmpSOA.cpp includes/BmpSOA.h)

add_executable(imgaos aos/image-aos.cpp)
target_link_libraries(imgaos common aos)

add_executable(imgsoa soa/image-soa.cpp)
target_link_libraries(imgsoa common soa)