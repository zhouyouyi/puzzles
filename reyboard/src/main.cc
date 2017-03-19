#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "ReyBoardConfig.h"
#include "ReyBoard.h"
#include "zutil.h"

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

    //std::cout << bconf << std::endl;

    ReyBoard board( bconf );

    //std::cout << board << std::endl;

    std::auto_ptr<std::ofstream> _ofp;

    if ( !output_file.empty() && output_file != "-" )
        _ofp.reset( new std::ofstream( output_file.c_str() ) );

    std::ostream& os = ( _ofp.get() ? *_ofp : std::cout );

    std::ifstream ifs( input_file.c_str() );
    std::string line;

    while ( std::getline( ifs, line ) )
    {
        const std::string s = trim(line);

        if ( s.empty() || s[0] == '#' ) continue;

        os << s << " -> ";

        Coord entry;

        if ( s[0] == 'C' )
        {
            if ( s[2] == '+' )
            {
                entry.x = 1;
                entry.y = s[1] - '0';
                entry.dir = DOWNWARDS;
            }
            else if ( s[2] == '-' )
            {
                entry.x = board.rows();
                entry.y = s[1] - '0';
                entry.dir = UPWARDS;
            }
        }
        else if ( s[0] == 'R' )
        {
            if ( s[2] == '+' )
            {
                entry.x = s[1] - '0';
                entry.y = 1;
                entry.dir = RIGHTWARDS;
            }
            else if ( s[2] == '-' )
            {
                entry.x = s[1] - '0';
                entry.y = board.columns();
                entry.dir = LEFTWARDS;
            }
        }

        Coord exit = board.shoot(entry);

        if ( ! board.absorbed(exit) )
        {
            os << exit << std::endl;
        }
        else
        {
            os << std::endl;
        }
    }

    return 0;
}
