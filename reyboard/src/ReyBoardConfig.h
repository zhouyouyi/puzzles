#ifndef REYBOARDCONFIG_H
#define REYBOARDCONFIG_H

#include <string>
#include <vector>

#define INFINITE_HP -1

struct MirrorConfig
{
    MirrorConfig() : x(0), y(0), hp(0) {} // needed by STL
    MirrorConfig( const int _x, const int _y, const int _hp )
        : x(_x), y(_y), hp(_hp) {}

    int x, y;
    int hp;
};

class ReyBoardConfig
{
public:
    typedef std::vector< MirrorConfig > MirrorConfigVec;

public:
    ReyBoardConfig(const std::string& config_file);

    void construct(const std::string& config_file);

    bool isValid() const { return m_board_size > 0; }

    const int size() const { return m_board_size; }

    const MirrorConfigVec& getMirrorConfigVec() const { return m_mirror_config_vec; }

private:
    int m_board_size;
    MirrorConfigVec m_mirror_config_vec;
};

std::ostream& operator << ( std::ostream& os, const MirrorConfig& o );
std::ostream& operator << ( std::ostream& os, const ReyBoardConfig& o );    

#endif
