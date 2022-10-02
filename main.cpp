#include "image.h"

// Entry point
int main(int argc, char *argv[])
{
    // Parse arguments
    if (arg_parser(argc, argv) < 0) {
        return (-1);
    }
    return (0);
}
