/*
  ID: zhou.yo1
  PROG: hamming
  LANG: C++
*/

#define PROG "hamming"

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

int hamming( int a, int b )
{
    int c = a ^ b;
    int d = 0;
    for(int i = 0; i < 8; ++i)
        if( (c &(1<<i)) != 0 ) d++;

    //cout << a << ' ' << b << ' ' << d << endl;

    return d;
}

bool dfs( vector<int>& ans, int start, int N, int B, int D, ostream& out )
{
    if( ans.size() == N )
    {
        int i;
        for(i = 0; i < ans.size(); ++i )
        {
            out << ans[i];
            if( (i+1) % 10 == 0 ) out << endl;
            else if( i != ans.size() - 1 ) out << ' ';
        }
        if( (i) % 10 != 0 )
            out << endl;

        return true;
    }

    for(int i = start; i < (1 << B); ++i)
    {
        int j;
        for(j = 0; j < ans.size(); ++j)
        {
            if( hamming( i, ans[j] ) < D ) break;
        }

        //out << i << ' ' << j << endl;

        if( j == ans.size() )
        {
            ans.push_back( i );
            if( dfs( ans, i+1, N, B, D, out ) ) return true;
            ans.pop_back();
        }
    }

    return false;
}

void solve( istream& fin, ostream& out )
{
    int N, B, D;
    fin >> N >> B >> D;

    // out << N << ' ' << B << ' ' << D << endl;

    vector<int> ans;

    dfs( ans, 0, N, B, D, out );
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
