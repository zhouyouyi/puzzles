/*
  ID: zhou.yo1
  PROG: skidesign
  LANG: C++
*/

#define PROG "skidesign"

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
    int N, i, j;
    long ans = numeric_limits<long>::max();
    fin >> N;

    vector<int> H(N);

    for(i = 0; i < N; ++i)
    {
        fin >> H[i];
    }

    sort(H.begin(), H.end());

    // for(i = 0; i < N; ++i)
    //     cout << "H[" << i << "]=" << H[i] << ' ';
    // cout << endl;

    if(N == 1)
    {
        out << (H.front() - 17) * (H.front() - 17) << endl;
        return;
    }

    if(H.back() - H.front() <= 17)
    {
        out << 0 << endl;
        return;
    }

    long cost = 0;
    for(i = 0; i < 84; ++i)
    {
        cost = 0;
        if(H.front() >= i)
        {
            cost = (H.front()-i)*(H.front()-i);
        }
        else
        {
            for(j = 0; j < N && H[j] < i; ++j)
            {
                cost += ((i - H[j]) * (i - H[j]));
            }
        }

        for(j = N-1; j >= 0 && H[j] - i > 17; --j)
        {
            cost += ((H[j] - i - 17) * (H[j] - i - 17));
        }

        ans = min(ans, cost);
    }

    out << ans << endl;
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

  solve( fin, out );

  return 0;
}
