/*
  ID: zhou.yo1
  PROG: numtri
  LANG: C++
*/

#define PROG "numtri"

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
    int N;
    fin >> N;

    vector<int> v1, v2;
    vector<int>* up = &v1, * down = &v2;

    up->push_back(0);

    int i,j,k;
    for(i = 1; i <= N; ++i)
    {
        for(j = 0; j < i; ++j)
        {
            fin >> k;
            int a = 0, b = 0;
            if( j-1 >= 0 )
            {
                a = k + up->at(j-1);
            }
            if( j < up->size() )
            {
                b = k + up->at(j);
            }

            down->push_back( max(a,b) );
        }

        swap(up, down);

        down->clear();
    }

    int ans = 0;
    for(i = 0; i < up->size(); ++i)
    {
        ans = max( ans, up->at(i) );
    }

    out << ans << endl;
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
