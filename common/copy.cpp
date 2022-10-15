//
// Created by Alvar on 15/10/2022.
//

#include "../includes/common.h"

int FileCopy(std::filesystem::path source, std::string target)
{
    std::filesystem::path finalpath = target / source.filename();
    if (!std::filesystem::copy_file(source, finalpath, std::filesystem::copy_options::overwrite_existing))
    {
        return(-1);
    }
    return (0);
}