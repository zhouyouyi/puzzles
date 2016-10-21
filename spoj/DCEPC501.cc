// C++11

#include <cstdint>
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

using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);

    int ncase;

    cin >> ncase;

    while(ncase--)
    {
        int N;
        cin >> N;

        vector< vector<long long> > T(4, vector<long long>(N+1, -1));

        vector<long long> A(N+1, 0);

        int i, j, k;

        for(i = 1; i <= N; ++i)
        {
            cin >> A[i];
        }

        T[1][1] = A[1];
        T[2][2] = A[1] + A[2];
        T[3][3] = A[1] + A[2] + A[3];
        T[1][3] = A[1] + A[3];

        for(i = 4; i <= N; ++i)
        {
            long long s = 0;
            for(j = 1; j <= 3; ++j)
            {
                s += A[i-j+1];
                for(k = 1; k <= 3; ++k)
                {
                    if( i-j-k >= 1 && T[k][i-j-k] != -1 )
                        T[j][i] = max( T[j][i], T[k][i-j-k] + s );
                }
            }
        }

        // for(i = 1; i <= 3; ++i)
        // {
        //     for(j = 1; j <= N; ++j)
        //     {
        //         cout << setw(4) << T[i][j];
        //     }
        //     cout << endl;
        // }

        long long ans = 0;

        for(i = 0; i <= 3; ++i)
        {
            for(j = i; j <= 3; ++j)
            {
                if( N-i > 0 )
                    ans = max( ans, T[j][N-i] );
            }
        }

        cout << ans << endl;
    }

    return 0;
}
