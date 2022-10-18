//
// Created by Alvar on 15/10/2022.
//

#include "../includes/common.h"

int FileCopy(const std::filesystem::path& source, const std::filesystem::path& target)
{
    std::filesystem::path finalpath = target / source.filename();
    if (!std::filesystem::copy_file(source, finalpath, std::filesystem::copy_options::overwrite_existing))
    {
        std::cerr << "Fallo al copiar archivo"<<std::endl;
        return(-1);
    }
    return (0
}