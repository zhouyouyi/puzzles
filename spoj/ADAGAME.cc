#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

typedef unsigned long long ull_t;
typedef long long ll_t;

int inc( int N, int K )
{
    int t = std::pow(10, K-1);
    int r = N % t;

    int d = (N / t) % 10;

    if( d == 9 )
        d = 0;
    else
        d++;

    return (N / (t*10) ) * (t*10) + d * t + r;
}

int main()
{
    int A[10000][101], V[10000][101];

    int i, j, k;

    for( i = 0; i < 10000; ++i )
    {
        A[i][0] = i;
        V[i][0] = i;
    }

    for(j = 1; j <= 100; ++j)
    {
        for(i = 0; i < 10000; ++i)
        {
            A[i][j] = 0;
            V[i][j] = 100000;

            for(k = 1; k <= 4; ++k)
            {
                int n = inc( i, k );

                A[i][j] = max( A[i][j], V[n][j-1] );
                V[i][j] = min( V[i][j], A[n][j-1] );
            }
        }
    }

    int T;
    cin >> T;

    while( T-- )
    {
        cin >> i >> j;

        if( A[i][j] > i )
            cout << "Ada" << endl;
        else
            cout << "Vinit" << endl;
    }
    return 0;
}
