/*
  ID: zhou.yo1
  PROG: subset
  LANG: C++
*/

#define PROG "subset"

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

void solve( istream& fin, ostream& out )
{
    int N, T;

    while( fin >> N )
    {
        T = N*(N+1) / 2;

        if( T % 2 ) out << 0 << endl;
        else
        {
            vector< vector<int> > D( T/2+1, vector<int>(N+1, 0) );
            D[0][0] = 1;

            for( int i = 1; i <= T/2; ++i )
            {
                for( int j = 1; j <= N; ++j )
                {
                    D[i][j] = D[i][j-1] + ( i < j ? 0 : D[i-j][j-1] );
                }
            }

            out << D[T/2][N] << endl;
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
