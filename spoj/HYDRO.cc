#include <iostream>

using namespace std;

int D[10001];

int main()
{
    int ncase;

    cin >> ncase;

    while(ncase--)
    {
        int N;

        cin >> N;

        int i, j, k;

        for(i = 0; i < N; ++i)
        {
            cin >> D[i];
        }

        int ans = 0;

        int hold = 0;

        j = 0;

        for(i = 0; i < N && D[i] == 0; i++);

        while( i < N && j < N )
        {
            for(j = i+1; j < N && D[j] < D[i]; ++j)
            {
                hold += (D[i] - D[j]);
            }

            if( j < N && D[j] >= D[i] )
            {
                i = j;
                ans += hold;

                hold = 0;
            }
        }

        for(j = N-1; j > i && D[j] == 0; --j);
        hold = 0;

        while( j > i )
        {
            for(k = j - 1; k >= i && D[k] < D[j]; --k)
            {
                hold += (D[j] - D[k]);
            }

            if( k >= i && D[k] >= D[j] )
            {
                j = k;
                ans += hold;

                hold = 0;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
