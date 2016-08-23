#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector< vector<int> > M(N, vector<int>(N, 0));

    int k;
    int i = 0, j = N/2;
    for(k = 1; k <= N*N; ++k)
    {
        M[i][j] = k;

        int oi = i, oj = j;

        i = ( i == 0 ? N - 1 : i - 1 );
        j = ( j == N - 1 ? 0 : j + 1 );

        if( M[i][j] != 0 )
        {
            i = ( oi == N - 1 ? 0 : oi + 1 );
            j = oj;
        }
    }

    for(i = 0; i < N; ++i )
    {
        for(j = 0; j < N; ++j)
        {
            cout << M[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
