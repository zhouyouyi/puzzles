/*
  ID: zhou.yo1
  PROG: combo
  LANG: C++
*/

#define PROG "combo"

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

set<int> C;

void solve( ifstream& fin, ofstream& out )
{
    int N, i, j, k;
    int a, b, c, T = 2;
    int pass[3];
    fin >> N;

    if( N == 1 ) { out << 1 << endl; return; }

    while( T-- )
    {
        for(i = 0; i < 3; ++i)
        {
            fin >> pass[i];
        }

        for(i = -2; i < 3; ++i)
        {
            a = pass[0] + i;
            if( a > N ) a -= N;
            if( a < 1 ) a += N;

            for(j = -2; j < 3; ++j)
            {
                b = pass[1] + j;
                if( b > N ) b -= N;
                if( b < 1 ) b += N;

                for(k = -2; k < 3; ++k)
                {
                    c = pass[2] + k;
                    if( c > N ) c -= N;
                    if( c < 1 ) c += N;

                    C.insert( a*100 + b*10 + c );
                }
            }
        }
    }

    out << C.size() << endl;
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

  solve( fin, out );

  return 0;
}
