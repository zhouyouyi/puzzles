/*
  ID: zhou.yo1
  PROG: nocows
  LANG: C++
*/

#define PROG "nocows"

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
    int N, K;

    fin >> N >> K;

    vector< vector<int> > T(K+1, vector<int>(N+1, 0));

    int i, j, k;

    for(i = 1; i <= K; ++i)
    {
        T[i][1] = 1;
    }

    for(i = 1; i <= K; ++i)
    {
        for(j = 1; j <= N; j += 2)
        {
            for(k = 1; k <= j-1; ++k)
            {
                T[i][j] = (T[i][j] + T[i-1][k]*T[i-1][j-k-1])%9901;
            }
        }
    }

    out << (T[K][N] + 9901 - T[K-1][N])%9901 << endl;
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
