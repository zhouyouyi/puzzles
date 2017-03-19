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
    Coord() : x(-1), y(-1), dir(NONE) {}
    Coord( int _x, int _y, Direction _dir ) : x(_y), y(_y), dir(_dir) {}
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

    Coord turnRight( const Coord& c );
    Coord turnLeft( const Coord& c );

    bool outside( const Coord& c );

    bool absorbed( const Coord& c );

    Coord disappear() { return Coord(); }

    void decreaseHP( int x, int y )
    {
        if ( hasMirror(x, y) && m_board[x][y] != INFINITE_HP )
            --m_board[x][y];
    }

    bool hasMirror( int x, int y )
    {
        return m_board[x][y] != 0;
    }

    int rows() const { return m_board.size()-1; }
    int columns() const { return m_board.front().size()-1; }

    void print( std::ostream& os ) const;

private:
    // a 2D array representing a board
    // 0 - no mirror
    // positive number - a mirror with given hp
    // negatvie number - a mirror with infinite hp
    typedef std::vector< std::vector< int > > BoardType;

    BoardType m_board;
};

std::ostream& operator << ( std::ostream& os, const Coord& o );
std::ostream& operator << ( std::ostream& os, const ReyBoard& o );

#endif
