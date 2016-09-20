/*
  ID: zhou.yo1
  PROG: concom
  LANG: C++
*/

#define PROG "concom"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

int shares[101][101] = {0};

void solve( istream& fin, ostream& out )
{
    int N, C = 0;
    fin >> N;
    int i,j,p;

    while(N--)
    {
        fin >> i >> j >> p;

        C = max( C, max(i, j) );

        shares[i][j] = p;
    }

    for(i = 1; i <= C; ++i)
    {
        deque<int> q;
        vector<bool> v(101, false);

        for(j = 1; j <= C; ++j)
        {
            if(j != i && shares[i][j] > 50 && !v[j])
                q.push_back(j);
        }

        while(q.size() > 0)
        {
            int n = q.front(); q.pop_front();

            if( v[n] ) continue;

            v[n] = true;

            for(p = 1; p <= C; ++p)
            {
                if( p != n ) shares[i][p] = min( 100, shares[i][p] + shares[n][p] );
            }

            for(j = 1; j <= C; ++j)
            {
                if( j != i && shares[i][j] > 50 && !v[j] ) q.push_back(j);
            }
        }
    }

#ifdef LOCAL
    for(i = 1; i <= C; ++i)
    {
        for(j = 1; j <= C; ++j)
        {
            out << setw(4) << shares[i][j];
        }
        out << endl;
    }
#endif

    for(i = 1; i <= C; ++i)
    {
        for(j = 1; j <= C; ++j)
        {
            if( j != i && shares[i][j] > 50 )
                out << i << ' ' << j << endl;
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
