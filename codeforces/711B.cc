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

int main()
{
    long N;
    cin >> N;

    if ( N == 1 )
    {
        cout << 1 << endl;
        return 0;
    }

    vector< vector<unsigned long long> > M(N, vector<unsigned long long>(N));

    int i, j, i_0, j_0;
    long long ans = 0;
    for ( i = 0; i < N; ++i )
    {
        for ( j = 0; j < N; ++j )
        {
            cin >> M[i][j];

            if ( M[i][j] == 0 )
            {
                i_0 = i;
                j_0 = j;
            }
        }
    }

    i = (i_0 + 1) % N;
    unsigned long long row = 0, col = 0;
    for ( j = 0; j < N; ++j )
    {
        row += M[i][j];
    }

    for ( j = 0; j < N; ++j )
    {
        row -= M[i_0][j];
    }

    M[i_0][j_0] = ans = row;

    if ( ans <= 0 )
    {
        cout << -1 << endl;
        return 0;
    }

    unsigned long long row_0 = 0, col_0 = 0;

    for ( j = 0; j < N; ++j )
        row_0 += M[i_0][j];

    for ( i = 0; i < N; ++i )
        col_0 += M[i][j_0];

    if ( row_0 != col_0 )
    {
        ans = - 1;

        cout << ans << endl;

        return 0;
    }

    for ( i = 0; i < N; ++i )
    {
        row = 0;

        for ( j = 0; j < N; ++j )
            row += M[i][j];

        if ( row != row_0 )
        {
            ans = -1;
            break;
        }
    }

    for ( j = 0; j < N; ++j )
    {
        col = 0;

        for ( i = 0; i < N; ++i )
        {
            col += M[i][j];
        }

        if ( col != col_0 )
        {
            ans = -1;
            break;
        }
    }

    unsigned long long d0 = 0, d1 = 0;

    for ( i = 0; i < N; ++i )
    {
        d0 += M[i][i];
        d1 += M[i][N-i-1];
    }

    if ( d0 != d1 || d0 != col_0 )
        ans = -1;

    if ( ans <= 0 )
        ans = -1;
    cout << ans << endl;
    return 0;
}
