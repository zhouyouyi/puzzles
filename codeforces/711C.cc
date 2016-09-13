#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

typedef unsigned long long ull_t;
typedef long long ll_t;

const static ull_t UINF = std::numeric_limits<ull_t>::max();
const static ll_t  INF  = std::numeric_limits<ll_t>::max();

using namespace std;

int main()
{
    int N, M, K;
    cin >> N >> M >> K;

    vector<int> C(N+1, 0);
    vector< vector<ull_t> > P( N+1, vector<ull_t>( M+1, 0 ) );

    int i, j, k, x;
    for( i = 1; i <= N; ++i )
        cin >> C[i];

    for( i = 1; i <= N; ++i )
        for( j = 1; j <= M; ++j )
            cin >> P[i][j];

    vector< vector< vector< ull_t > > > T( N+1, vector< vector< ull_t > >( K+1, vector<ull_t>( M+1, UINF ) ) );

    if( C[1] )
    {
        T[1][1][C[1]] = 0;
    }
    else
    {
        for(i = 1; i <= M; ++i)
        {
            T[1][1][i] = P[1][i];
        }
    }

    for( i = 2; i <= N; ++i )
    {
        for( k = 1; k <= i && k <= K; ++k )
        {
            for( j = 1; j <= M; ++j )
            {
                if( C[i] == 0 )
                {
                    ull_t cost = ( T[i-1][k][j] == UINF ? UINF : T[i-1][k][j] + P[i][j] );

                    for( x = 1; x <= M; ++x )
                    {
                        if( x != j )
                        {
                            cost = std::min( cost,
                                             ( T[i-1][k-1][x] == UINF ? UINF : T[i-1][k-1][x] + P[i][j] ) );
                        }
                    }

                    T[i][k][j] = cost;
                }
                else if( C[i] == j )
                {
                    ull_t cost = ( T[i-1][k][j] == UINF ? UINF : T[i-1][k][j] );

                    for( x = 1; x <= M; ++x )
                    {
                        if( x != j )
                        {
                            cost = std::min( cost,
                                             ( T[i-1][k-1][x] == UINF ? UINF : T[i-1][k-1][x] ) );
                        }
                    }

                    T[i][k][j] = cost;
                }
                else
                {
                    T[i][k][j] = UINF;
                }
            }
        }
    }

    /*
    for( i = 1; i <= N; ++i )
    {
        cout << "n = " << i << endl;
        for( int a = 1; a <= K; ++a )
        {
            for( int b = 1; b <= M; ++b )
            {
                cout << setw(4);
                if( T[i][a][b] == UINF )
                    cout << "INF";
                else
                    cout << T[i][a][b];
            }
            cout << endl;
        }
        cout << endl;
    }
    */

    ull_t ans = UINF;

    for( i = 1; i <= M; ++i )
        ans = std::min( ans, T[N][K][i] );

    if( ans == UINF )
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}
