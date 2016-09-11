/*
  ID: zhou.yo1
  PROG: preface
  LANG: C++
*/

#define PROG "preface"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <cstring>

using namespace std;

char * romanize( int num )
{
    static char buf[256];
    int pos = 0;

    while ( num >= 1000 ) // M
    {
        buf[pos++] = 'M';
        num -= 1000;
    }

    if ( ( num / 100 ) % 10 == 4 )
    {
        buf[pos++] = 'C';
        buf[pos++] = 'D';
        num %= 100;
    }
    else if ( ( num / 100 ) % 10 == 9 )
    {
        buf[pos++] = 'C';
        buf[pos++] = 'M';
        num %= 100;
    }
    else
    {
        while ( num >= 500 ) // D
        {
            buf[pos++] = 'D';
            num -= 500;
        }

        while ( num >= 100 ) // C
        {
            buf[pos++] = 'C';
            num -= 100;
        }
    }

    if ( ( num / 10 ) % 10 == 4 )
    {
        buf[pos++] = 'X';
        buf[pos++] = 'L';
        num %= 10;
    }
    else if ( ( num / 10 ) % 10 == 9 )
    {
        buf[pos++] = 'X';
        buf[pos++] = 'C';
        num %= 10;
    }
    else
    {
        while ( num >= 50 ) // L
        {
            buf[pos++] = 'L';
            num -= 50;
        }

        while ( num >= 10 ) // X
        {
            buf[pos++] = 'X';
            num -= 10;
        }
    }

    if ( ( num ) % 10 == 4 )
    {
        buf[pos++] = 'I';
        buf[pos++] = 'V';
        //num %= 100;
    }
    else if ( ( num ) % 10 == 9 )
    {
        buf[pos++] = 'I';
        buf[pos++] = 'X';
        //num %= 100;
    }
    else
    {
        while ( num >= 5 ) // V
        {
            buf[pos++] = 'V';
            num -= 5;
        }

        while ( num >= 1 ) // I
        {
            buf[pos++] = 'I';
            num -= 1;
        }
    }

    buf[pos] = '\0';

    return buf;
}

void solve( istream& fin, ostream& out )
{
    int num;

    map<char, int> count;
    const char* seq = "IVXLCDM";

    for( int i = 0; i < strlen(seq); ++i )
    {
        count[seq[i]] = 0;
    }

    while( fin >> num )
    {
        for( int k = 1; k <= num; k++ )
        {
            char * p = romanize(k);

            //out << p << endl;

            for( int i = 0; i < strlen(p); ++i )
            {
                count[p[i]]++;
            }
        }

        for( int i = 0; i < strlen(seq); ++i )
        {
            if( count[seq[i]] == 0 ) break;
            out << seq[i] << ' ' << count[seq[i]] << endl;
        }
    }
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
