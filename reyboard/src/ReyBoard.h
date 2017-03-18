#ifndef REYBOARD_H
#define REYBOARD_H

#include <ostream>
#include <string>
#include <vector>

#include "ReyBoardConfig.h"

enum Direction
{
    NONE = 0,
    UPWARDS = 1,
    RIGHTWARDS = 2,
    DOWNWARDS = 3,
    LEFTWARDS = 4
};

struct Coord
{
    int x, y;
    Direction dir;
};

class ReyBoard
{
public:
    ReyBoard( const ReyBoardConfig& config );

    Coord shoot( const Coord& c );

    Coord move( const Coord& c );

    Coord next( const Coord& c );

    Coord prev( const Coord& c );

    bool outside( const Coord& c );

    bool absorbed( const Coord& c );

    void print( std::ostream& os ) const;

private:
    // a 2D array representing a board
    // 0 - no mirror
    // positive number - a mirror with given hp
    // negatvie number - a mirror with infinite hp
    typedef std::vector< std::vector< int > > BoardType;

    BoardType m_board;
};

std::ostream& operator << ( std::ostream& os, const ReyBoard& o );

#endif
