//
// Created by Alvar on 15/10/2022.
//

#include "../includes/common.h"

/*The function Filecopy gets 2 paths from param, first one is the file from the source path
 * from the file that needs to be copied, the second one is the directory where it is going to be copied.
 * It returns 0 on success and -1 when fails */
int FileCopy(const std::filesystem::path& source, const std::filesystem::path& target)
{
    //First, the path of the copy is going to be the path of the target directory plus the name of the file
    std::filesystem::path finalpath = target / source.filename();
    //Then it copies the file and returns -1 if fails
    if (!std::filesystem::copy_file(source, finalpath, std::filesystem::copy_options::overwrite_existing))
    {
        std::cerr << "Fallo al copiar archivo"<<std::endl;
        return(-1);
    }
    return (0);
}