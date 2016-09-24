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

typedef unsigned long long ull_t;
typedef long long ll_t;

const static int inf = std::numeric_limits<int>::max();

int main()
{
    int T, N, K;
    cin >> T;

    while(T--)
    {
        cin >> N >> K;

        int D[101][101][101] = { inf };

        vector< int > M(K+1, 0);

        int i, j, k, n;

        D[0][0][0] = 0;

        for(i = 1; i <= K; ++i)
            cin >> M[i];

        for(i = 0; i <= K; ++i)
            for(n = 0; n <= N; ++n)
                for(k = 0; k <= K; ++k)
                    D[i][n][k] = inf;

        for(i = 0; i <= K; ++i)
            for(n = 0; n <= N; ++n)
                D[i][n][0] = 0;

        int ans = inf;
        for(i = 1; i <= K; ++i)
        {
            for(n = 1; n <= N; ++n)
            {
                for(k = 1; k <= K; ++k)
                {
                    if( M[i] == -1 )
                        D[i][n][k] = D[i-1][n][k];
                    else
                        for( j = 0; j <= k/i && j <= n; ++j )
                            D[i][n][k] = min( D[i][n][k],
                                              ( D[i-1][n-j][k-j*i] == inf ? inf : D[i-1][n-j][k-j*i] + M[i]*j ) );
                }

                ans = min( ans, D[i][n][K] );
            }
        }

        cout << (ans == std::numeric_limits<int>::max() ? -1 : ans ) << endl;
    }
    return 0;
}
