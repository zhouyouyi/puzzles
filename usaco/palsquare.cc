/*
  ID: zhou.yo1
  PROG: palsquare
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

void to_base( int num, int base, char* out )
{
    char* p = out;

    while( num )
    {
        *p++ = digits[ num % base ];
        num /= base;
    }
    *p = '\0';

    reverse( out, p );

    //cout << out << endl;
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
    ifstream fin( "palsquare.in" );
    ofstream out( "palsquare.out" );

    int base;
    fin >> base;

    char N[256];
    char S[256];

    for(int i = 1; i <= 300; ++i )
    {
        to_base(i, base, N);
        to_base(i*i, base, S);

        if( is_pal(S, strlen(S)) )
        {
            out << N << ' ' << S << endl;
        }
    }

    return 0;
}
