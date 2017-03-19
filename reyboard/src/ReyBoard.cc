#include <iomanip>
#include <stdexcept>

#include "ReyBoard.h"

ReyBoard::ReyBoard(const ReyBoardConfig& config )
    : m_board( config.size()+1, std::vector<int>( config.size()+1, 0 ) )
{
    const ReyBoardConfig::MirrorConfigVec& vec = config.getMirrorConfigVec();

    int len = vec.size();
    for ( int i = 0; i < len; ++i )
    {
        m_board[vec[i].x][vec[i].y] = vec[i].hp;
    }
};

bool ReyBoard::outside(const Coord &c)
{
    int row = m_board.size();
    int col = m_board.front().size();

    return c.x < 1 || c.y < 1 || c.x >= row || c.y >= col;
}

bool ReyBoard::absorbed(const Coord &c)
{
    return c.x == -1 && c.y == -1;
}

Coord ReyBoard::next( const Coord& c )
{
    Coord _next;
    if ( c.dir == UPWARDS )
    {
        _next.x = c.x - 1;
        _next.y = c.y;
        _next.dir = c.dir;
    }
    else if ( c.dir == DOWNWARDS )
    {
        _next.x = c.x + 1;
        _next.y = c.y;
        _next.dir = c.dir;
    }
    else if ( c.dir == LEFTWARDS )
    {
        _next.x = c.x;
        _next.y = c.y - 1;
        _next.dir = c.dir;
    }
    else if ( c.dir == RIGHTWARDS )
    {
        _next.x = c.x;
        _next.y = c.y + 1;
        _next.dir = c.dir;
    }

    return _next;
}

Coord ReyBoard::prev( const Coord& c )
{
    Coord _prev;
    if ( c.dir == UPWARDS )
    {
        _prev.x = c.x + 1;
        _prev.y = c.y;
        _prev.dir = c.dir;
    }
    else if ( c.dir == DOWNWARDS )
    {
        _prev.x = c.x - 1;
        _prev.y = c.y;
        _prev.dir = c.dir;
    }
    else if ( c.dir == LEFTWARDS )
    {
        _prev.x = c.x;
        _prev.y = c.y + 1;
        _prev.dir = c.dir;
    }
    else if ( c.dir == RIGHTWARDS )
    {
        _prev.x = c.x;
        _prev.y = c.y - 1;
        _prev.dir = c.dir;
    }

    return _prev;
}

Coord ReyBoard::shoot( const Coord& c )
{
    Coord exit;

    if ( hasMirror(c.x, c.y) )
    {
        decreaseHP(c.x, c.y);
        return disappear();
    }

    int row = m_board.size();
    int col = m_board.front().size();

    // special rule for mirrors on the borders
    if ( c.dir == UPWARDS || c.dir == DOWNWARDS )
    {
        if ( c.y-1 > 0 && hasMirror(c.x, c.y-1) )
        {
            decreaseHP( c.x, c.y-1 );
            exit.x = c.x;
            exit.y = c.y;
            exit.dir = NONE;
            return exit;
        }
        if ( c.y+1 < col && hasMirror(c.x, c.y+1) )
        {
            decreaseHP( c.x, c.y+1 );
            exit.x = c.x;
            exit.y = c.y;
            exit.dir = NONE;
            return exit;
        }
    }
    else if ( c.dir == LEFTWARDS || c.dir == RIGHTWARDS )
    {
        if ( c.x-1 > 0 && hasMirror(c.x-1, c.y) )
        {
            decreaseHP( c.x-1, c.y );
            exit.x = c.x;
            exit.y = c.y;
            exit.dir = NONE;
            return exit;
        }
        if ( c.x+1 < row && hasMirror(c.x+1, c.y) )
        {
            decreaseHP( c.x+1, c.y );
            exit.x = c.x;
            exit.y = c.y;
            exit.dir = NONE;
            return exit;
        }
    }

    // it survived the border
    Coord n = next( c );

    // assumes there is no ray loop inside the board
    // by how mirrors deflect rays, there *probably* shouldn't form any loop
    // I am not sure about it, I tried to construct a ray loop but couldn't.
    while ( true )
    {
        if ( absorbed( n ) ) return n;

        if ( outside( n ) ) return prev(n);

        n = move( n );
    }

    // are we ever going to get here?
    return n;
}

Coord ReyBoard::move(const Coord &c)
{
    Coord exit;

    if ( hasMirror( c.x, c.y ) )
    {
        decreaseHP( c.x, c.y );
        return disappear();
    }

    int row = m_board.size();
    int col = m_board.front().size();
    int cx = c.x, cy = c.y;

    // rules for deflection
    switch( c.dir )
    {
    case UPWARDS:
    {
        if ( cx-1 > 0 && cy+1 < col && hasMirror(cx-1, cy+1) )
        {
            decreaseHP(cx-1, cy+1);
            return turnLeft(c);
        }

        if ( cx-1 > 0 && cy-1 > 0 && hasMirror(cx-1, cy-1) )
        {
            decreaseHP(cx-1, cy-1);
            return turnRight(c);
        }

        return next(c);
    }
    break;
    case DOWNWARDS:
    {
        if ( cx+1 < row && cy+1 < col && hasMirror(cx+1, cy+1) )
        {
            decreaseHP(cx+1, cy+1);
            return turnRight(c);
        }

        if ( cx+1 < row && cy-1 > 0 && hasMirror(cx+1, cy-1) )
        {
            decreaseHP(cx+1, cy-1);
            return turnLeft(c);
        }

        return next(c);
    }
    break;
    case RIGHTWARDS:
    {
        if ( cx-1 > 0 && cy+1 < col && hasMirror(cx-1, cy+1) )
        {
            decreaseHP(cx-1, cy+1);
            return turnRight(c);
        }

        if ( cx+1 < row && cy+1 < col && hasMirror(cx+1, cy+1) )
        {
            decreaseHP(cx+1, cy+1);
            return turnLeft(c);
        }

        return next(c);
    }
    break;
    case LEFTWARDS:
    {
        if ( cx-1 > 0 && cy-1 > 0 && hasMirror(cx-1, cy-1) )
        {
            decreaseHP(cx-1, cy-1);
            return turnLeft(c);
        }

        if ( cx+1 < row && cy-1 > 0 && hasMirror(cx+1, cy-1) )
        {
            decreaseHP(cx+1, cy-1);
            return turnRight(c);
        }

        return next(c);
    }
    break;
    case NONE:
        break;
    }

    // should never reach here
    return exit;
}

Coord ReyBoard::turnRight(const Coord &c)
{
    Coord n = c;

    switch( n.dir )
    {
    case UPWARDS: n.dir = RIGHTWARDS; return n;
    case DOWNWARDS: n.dir = LEFTWARDS; return n;
    case RIGHTWARDS: n.dir = DOWNWARDS; return n;
    case LEFTWARDS: n.dir = UPWARDS; return n;
    case NONE: break;
    }

    // should never reach here
    return n;
}

Coord ReyBoard::turnLeft(const Coord &c)
{
    Coord n = c;

    switch( n.dir )
    {
    case UPWARDS: n.dir = LEFTWARDS; return n;
    case DOWNWARDS: n.dir = RIGHTWARDS; return n;
    case RIGHTWARDS: n.dir = UPWARDS; return n;
    case LEFTWARDS: n.dir = DOWNWARDS; return n;
    case NONE: break;
    }

    // should never reach here
    return n;
}

void ReyBoard::print( std::ostream& os ) const
{
    int iend = m_board.size();
    int jend = m_board.front().size();
    for ( int i = 1; i < iend; ++i )
    {
        for ( int j = 1; j < jend; ++j )
        {
            os << std::setw(4) << m_board[i][j];
        }
        os << std::endl;
    }
}

std::ostream& operator << ( std::ostream& os, const ReyBoard& o )
{
    o.print( os );
    return os;
}

std::ostream& operator << ( std::ostream& os, const Coord& o )
{
    return os << "{" << o.x << "," << o.y << "}";
}
