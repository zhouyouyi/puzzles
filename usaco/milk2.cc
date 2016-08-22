/*
  ID: zhou.yo1
  PROG: milk2
  LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct line_t
{
    line_t() : left(0), right(0) {}
    line_t( int l, int r ) : left(l), right(r) {}
    int left;
    int right;
};

bool comp( const line_t& a, const line_t& b )
{
    return a.left < b.left || (a.left == b.left && a.right < b.right );
}

int main()
{
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");

    int i, N;
    fin >> N;

    vector< line_t > L(N);

    for( i = 0; i < N; ++i )
    {
        fin >> L[i].left >> L[i].right;
    }

    sort( L.begin(), L.end(), comp );

    line_t cur = L[0];

    int work = 0;
    int idle = 0;

    for( i = 1; i < N; ++i )
    {
        if( L[i].left > cur.right )
        {
            work = max( work, cur.right - cur.left );
            idle = max( idle, L[i].left - cur.right );

            cur = L[i];
        }
        else
        {
            cur.right = max( cur.right, L[i].right );
        }
    }

    work = max( work, cur.right - cur.left );

    // cout << work << ' ' << idle << endl;

    fout << work << ' '<< idle << endl;

    return 0;
}
