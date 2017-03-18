#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "ReyBoardConfig.h"
#include "ReyBoard.h"

static void usage(const char* progname)
{
    std::cout << "usage: " << progname << " <config> <input> [output]" << std::endl
              << "       config - the board config file" << std::endl
              << "       input  - ray input file" << std::endl
              << "       ouput  - ray output file, print to STDOUT if omitted" << std::endl
              << "Build Time: " << __DATE__ << " " << __TIME__ << std::endl;
}

int main( int argc, char* argv[] )
{
    if ( argc != 3 && argc != 4)
    {
        usage(argv[0]);
        return -1;
    }

    std::string config_file(argv[1]);
    std::string input_file(argv[2]);
    std::string output_file(argc == 4 ? argv[3] : "-");

    ReyBoardConfig bconf(config_file);

    std::cout << bconf << std::endl;

    ReyBoard board( bconf );

    std::cout << board << std::endl;

    return 0;
}
