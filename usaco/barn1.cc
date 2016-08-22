/*
  ID: zhou.yo1
  PROG: barn1
  LANG: C++
*/

#define PROG "barn1"

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

void solve( ifstream& fin, ofstream& out )
{
    int M, S, C;
    fin >> M >> S >> C;

    vector<int> stalls(S+1, 0);
    int i, j, cow, ans;

    for(i = 0; i < C; ++i)
    {
        fin >> cow;
        stalls[cow] = 1;
    }

    for(i = 1; i <= S && stalls[i] == 0; ++i);
    for(j = S; j >= 1 && stalls[j] == 0; --j);

    ans = j - i + 1;

    M--;

    while(M--)
    {
        int ms = 0, me = 0, s = 0, e = 0;
        for(cow = i; cow <= j; ++cow)
        {
            if( stalls[cow] )
            {
                if( e - s > me - ms )
                {
                    ms = s;
                    me = e;
                }

                s = cow;
                e = cow;
            }
            else
            {
                e = cow;
            }
        }

        ans -= (me - ms);

        for(; ms <= me; ++ms) stalls[ms] = 1;
    }

    out << ans << endl;

    // cout << ans << endl;
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

  solve( fin, out );

  return 0;
}
