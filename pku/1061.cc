#include <iostream>

using namespace std;

long long gcd_ext( long long a, long long b, long long& x, long long& y )
{
    if( b == 0 )
    {
        x = 1;
        y = 0;

        return a;
    }

    long long g = gcd_ext( b, a%b, x, y );

    long long t = x;
    x = y;
    y = t - (a/b)*y;

    return g;
}

int main()
{
    long long X, Y, M, N, L;

    cin >> X >> Y >> M >> N >> L;

    long long A = N - M;
    long long B = L;
    long long C = X - Y;

    long long x, y;
    long long G = gcd_ext( A, B, x, y );

    if( C % G )
    {
        cout << "Impossible" << endl;
        return 0;
    }

    x = x * (C/G);
    y = y * (C/G);

    // x = x0 + (B/G)*t

    long long k = x * G/B;
    k = x - k * B/G;

    if( k < 0 )
        k += B/G;

    cout << k << endl;

    return 0;
}
