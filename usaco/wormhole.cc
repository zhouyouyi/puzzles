/*
  ID: zhou.yo1
  PROG: wormhole
  LANG: C++
*/

#define PROG "wormhole"

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

#define MAX_N 12

long N, X[MAX_N+1], Y[MAX_N+1];
vector<long> chain(MAX_N+1, 0);
vector<long> right_next(MAX_N+1, 0);

bool cycle_exists()
{
    for(int start = 1; start <= N; ++start)
    {
        int pos = start;

        for(int count = 0; count < N; ++count )
        {
            pos = right_next[ chain[pos] ];
        }

        if( pos != 0 ) return true;
    }

    return false;
}

int answer()
{
    // find the first one that is not paired
    int i , total = 0;
    for(i = 1; i <= N; i++)
        if( chain[i] == 0 ) break;

    if(i > N)
    {
        if( cycle_exists() ) return 1;
        else return 0;
    }

    for(int j = i + 1; j <= N; ++j)
    {
        if( chain[j] == 0 )
        {
            chain[i] = j;
            chain[j] = i;

            total += answer();

            chain[i] = chain[j] = 0;
        }
    }

    return total;
}

void solve( ifstream& fin, ofstream& out )
{
    int i, j;
    fin >> N;

    for(i = 1; i <= N; ++i)
    {
        fin >> X[i] >> Y[i];
    }

    for(i = 1; i <= N; ++i)
    {
        for(j = 1; j <= N; j++ )
        {
            if( X[j] > X[i] && Y[i] == Y[j] )
            {
                if(right_next[i] == 0 || X[j] - X[i] < X[right_next[i]] - X[i])
                    right_next[i] = j;
            }
        }
    }

    out << answer() << endl;
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

  solve( fin, out );

  return 0;
}
