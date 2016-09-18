/*
  ID: zhou.yo1
  PROG: prefix
  LANG: C++
*/

#define PROG "prefix"

#include <iomanip>
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
    set<string> P;

    string t;

    while( fin >> t )
    {
        if( t == "." ) break;

        P.insert( t );
    }

    string S;

    while( fin >> t) S.append(t);

    //out << S << endl;

    vector<int> T;
    int i, j;
    int N = S.size();
    int ans = 0;

    if( P.count( S.substr(0, 1) ) ) T.push_back(1);
    else T.push_back(-1);

    for(i = 1; i < N; ++i)
    {
        bool found = false;
        for(j = i; j >= 0 && i - j + 1 <= 10; --j)
        {
            if( (T[j-1] != -1) && P.count( S.substr(j, i-j+1) ) > 0 )
            {
                found = true;
                ans = max( ans, i + 1 );
            }
        }

        if( !found )
        {
            T.push_back(-1);
        }
        else
        {
            T.push_back(i+1);
        }
    }

#ifdef LOCAL
    for(i = 0; i < T.size(); ++i)
    {
        out << setw(10) << T[i];
    }
    out << endl;
#endif

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
