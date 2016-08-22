/*
  ID: zhou.yo1
  PROG: crypt1
  LANG: C++
*/

#define PROG "crypt1"

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

void gen( vector<int>& D, vector<int>& out, int k )
{
    deque<int> q;

    q.push_back(0);

    while( q.size() > 0 )
    {
        if( q.size() < k )
        {
            q.push_back(0);
        }
        else
        {
            int num = 0;
            for(int i = 0; i < q.size(); i++) num = num*10 + D[q[i]];

            out.push_back(num);

            while( q.size() > 0 && q.back() + 1 > D.size() - 1 )
            {
                q.pop_back();
            }

            if( q.size() > 0 ) q.back()++;
        }
    }
}

bool is_ok( int num, vector<int>& D, int k )
{
    int d, cnt = 0;

    while( num )
    {
        d = num % 10;
        num /= 10;

        cnt++;

        bool found = false;

        for(int i = 0; i < D.size(); ++i)
        {
            if(D[i] == d) { found = true; break; }
        }

        if( !found ) return false;
    }

    if( cnt != k ) return false;

    return true;
}

void solve( ifstream& fin, ofstream& out )
{
    int N;
    fin >> N;
    vector<int> digits(N);
    int i, j, ans = 0;

    for(i = 0; i < N; ++i)
    {
        fin >> digits[i];
    }

    vector<int> num3, num2;

    gen( digits, num3, 3 );
    gen( digits, num2, 2 );

    //for(i = 0; i < num2.size(); ++i)
    //    cout << num2[i] << endl;

    for(i = 0; i < num3.size(); ++i)
    {
        for(j = 0; j < num2.size(); ++j)
        {
            if( ! is_ok( num3[i]*num2[j], digits, 4 ) ) continue;
            if( ! is_ok( num3[i]*(num2[j]/10), digits, 3 ) ) continue;
            if( ! is_ok( num3[i]*(num2[j]%10), digits, 3 ) ) continue;

            // cout << num3[i] << ' ' << num2[j] << endl;

            ans++;
        }
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
