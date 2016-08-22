/*
  ID: zhou.yo1
  PROG: dualpal
  LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const char* digits = "0123456789ABCDEFGHIJKLMN";

int to_base( int num, int base, char* out )
{
    char* p = out;

    while( num )
    {
        *p++ = digits[ num % base ];
        num /= base;
    }
    *p = '\0';

    reverse( out, p );

    // cout << out << endl;

    return p - out;
}

bool is_pal( char* in, int len )
{
    for(int i = 0; i < len/2; ++i )
    {
        if( in[i] != in[len-1-i] ) return false;
    }

    return true;
}

int main()
{
    ifstream fin( "dualpal.in" );
    ofstream out( "dualpal.out" );

    int N, S;
    fin >> N >> S;

    S++;

    char buf[256];

    while( N )
    {
        int count = 0;
        for( int b = 2; b <= 10; ++b )
        {
            int len = to_base( S, b, buf );

            if( is_pal( buf, len ) )
            {
                count++;
            }
        }

        if( count >= 2 )
        {
            out << S << endl;
            N--;
        }

        S++;
    }

    return 0;
}
