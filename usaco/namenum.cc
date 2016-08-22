/*
  ID: zhou.yo1
  PROG: namenum
  LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

set<string> dict;

char M[10][3] = {
    { '\0', '\0', '\0' },
    { '\0', '\0', '\0' },
    { 'A', 'B', 'C' },
    { 'D', 'E', 'F' },
    { 'G', 'H', 'I' },
    { 'J', 'K', 'L' },
    { 'M', 'N', 'O' },
    { 'P', 'R', 'S' },
    { 'T', 'U', 'V' },
    { 'W', 'X', 'Y' }
};

bool found = false;

void solve( const string& num, char* buf, int start, int len, ofstream& out )
{
    if( num[start] == '1' || num[start] == '0' )
    {
        out << "NONE" << endl;
        return;
    }

    if( start == len )
    {
        buf[start] = '\0';

        // cout << buf << endl;

        if( dict.find( buf ) != dict.end() )
        {
            found = true;
            out << buf << endl;
        }
        return;
    }

    for( int i = 0; i < 3; ++i )
    {
        buf[start] = M[ num[start] - '0' ][i];

        solve( num, buf, start+1, len, out );
    }
}

int main()
{
    ifstream fin("namenum.in");
    ifstream fdt("dict.txt");
    ofstream out("namenum.out");

    string num, s;

    while( fdt >> s )
    {
        dict.insert( s );
    }

    fin >> num;

    char buf[16];
    solve( num, buf, 0, num.size(), out );

    if ( !found ) out << "NONE" << endl;
    return 0;
}
