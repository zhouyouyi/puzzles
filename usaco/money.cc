/*
  ID: zhou.yo1
  PROG: money
  LANG: C++
*/

#define PROG "money"

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

typedef unsigned long long ull_t;

void solve( istream& fin, ostream& out )
{
    int V, N;
    fin >> V >> N;

    int i, j, k;
    vector<int> coin(V+1, 0);

    for(i = 1; i <= V; ++i)
        fin >> coin[i];

    vector< vector<ull_t> > T( V+1, vector<ull_t>( N+1, 0 ) );

    for(i = 0; i <= V; ++i)
        T[i][0] = 1;

    for(i = 1; i <= V; ++i)
    {
        for(j = 1; j <= N; ++j)
        {
            for(k = 0; j - k*coin[i] >= 0; ++k)
                T[i][j] += T[i-1][j-k*coin[i]];
        }
    }

    out << T[V][N] << endl;
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
