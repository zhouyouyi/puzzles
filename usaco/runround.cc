/*
  ID: zhou.yo1
  PROG: runround
  LANG: C++
*/

#define PROG "runround"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

bool is_runaround( unsigned long num )
{
    char buf[16];
    int len = sprintf( buf, "%lu", num );

    vector<bool> flag(10, true);
    int i;
    for ( i = 0; i < len; ++i )
    {
        if( ! flag[buf[i] - '0'] ) return false;

        flag[buf[i] - '0'] = false;
    }

    char d = buf[0];
    int pos = 0;
    std::fill( flag.begin(), flag.end(), true );

    for ( i = 0; i < len; ++i )
    {
        pos = (pos + d - '0') % len;

        if( ! flag[buf[pos]-'0'] ) return false;

        flag[buf[pos]-'0'] = false;

        d = buf[pos];
    }

    return pos == 0;
}

void solve( istream& fin, ostream& out )
{
    unsigned long N;
    fin >> N;

    do
    {
        N++;
    } while( ! is_runaround( N ) );

    out << N << endl;
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

#ifdef LOCAL
  solve( cin, cout );
#else
  solve( fin, out );
#endif

  return 0;
}
