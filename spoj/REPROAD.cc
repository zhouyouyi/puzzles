#include <iostream>
#include <iomanip>

using namespace std;

int T[10001][10001];
int A[10001];

int main()
{
    int ncase;
    cin >> ncase;

    while(ncase--)
    {
        int N, K;

        cin >> N >> K;

        int i, cur = 0, k;

        for( i = 1; i <= N; ++i)
        {
            cin >> A[i];

            if(A[i])
            {
                cur++;

                T[0][i] = cur;
            }
            else
            {
                cur = 0;

                T[0][i] = 0;
            }
        }

        int ans = 0;

        for( k = 1; k <= K; ++k )
        {
            for( i = 1; i <= N; ++i )
            {
                if(A[i])
                    T[k][i] = T[k][i-1]+1;
                else
                    T[k][i] = T[k-1][i-1]+1;

                ans = max( ans, T[k][i] );
            }
        }

        // for(k = 0; k <= K; ++k)
        // {
        //     for(i = 1; i <= N; ++i)
        //     {
        //         cout << setw(3) << T[k][i];
        //     }
        //     cout << endl;
        // }

        cout << ans << endl;
    }
    return 0;
}
