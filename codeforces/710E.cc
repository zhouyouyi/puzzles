#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    long N, X, Y;
    cin >> N >> X >> Y;

    vector<long long> T(N+1, 0);

    T[1] = X;

    long i;
    for(i = 2; i <= N; ++i)
    {
        T[i] = T[i-1] + X;

        if( i % 2 )
        {
            T[i] = min( T[i], T[i/2+1] + Y + X );
        }
        else
        {
            T[i] = min( T[i], T[i/2] + Y );
        }
    }

    cout << T[N] << endl;

    return 0;
}
