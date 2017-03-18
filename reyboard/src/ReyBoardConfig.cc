#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ReyBoardConfig.h"
#include "zutil.h"

ReyBoardConfig::ReyBoardConfig( const std::string& config_file )
    : m_board_size(0)
{
    construct( config_file );

    if ( ! isValid() )
        throw std::logic_error( "Cannot constuct valid board config from file" );
}

void ReyBoardConfig::construct( const std::string& config_file )
{
    std::string line;
    std::ifstream ifs( config_file.c_str() );

    while ( std::getline( ifs, line ) )
    {
        std::string s = trim( line );

        if ( s.empty() || s[0] == '#' ) continue;

        std::istringstream iss(s);

        if ( m_board_size == 0 )
        {
            iss >> m_board_size;

            if ( m_board_size <= 0 )
            {
                std::cerr << "Can't construct a board with non-positive count of holes" << std::endl;
                return;
            }
        }
        else
        {
            MirrorConfig mc;

            iss >> mc.x >> mc.y;

            if ( ! (iss >> mc.hp) )
                mc.hp = INFINITE_HP;

            m_mirror_config_vec.push_back( mc );
        }
    }   
}

std::ostream& operator << ( std::ostream& os, const MirrorConfig& o )
{
    os << "{" << o.x << "," << o.y;

    if ( o.hp != INFINITE_HP )
        os << "," << o.hp;
    os << "}";

    return os;
}

std::ostream& operator << ( std::ostream& os, const ReyBoardConfig& o )
{
    os << "{" << o.size() << ",[";

    const ReyBoardConfig::MirrorConfigVec& vec = o.getMirrorConfigVec();

    for ( int i = 0; i < vec.size(); ++i )
    {
        os << vec[i];

        if ( i != vec.size() - 1 ) os << ",";
    }
    os << "]}";

    return os;
}
