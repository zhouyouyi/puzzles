#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll_t;

long long gcd_ext( ll_t a, ll_t b, ll_t& x, ll_t& y )
{
    ll_t t, g;
    if( b == 0 )
    {
        x = 1;
        y = 0;
        return a;
    }

    g = gcd_ext( b, a%b, x, y );
    t = x;
    x = y;
    y = t - a/b*y;

    return g;
}

int main()
{
    long long a1, b1, a2, b2, L, R;
    cin >> a1 >> b1 >> a2 >> b2 >> L >> R;

    ll_t A = a1;
    ll_t B = a2;
    ll_t C = abs(b2 - b1);

    ll_t X, Y;
    ll_t G = gcd_ext( A, B, X, Y );

    if( C % G )
    {
        cout << 0 << endl;
        return 0;
    }

    X = X*C/G;
    Y = Y*C/G;

    // X + B/G*k
    // Y - A/G*k
    // a1 * (X + B/G*k) + b1 >= L
    // a2 * (Y - A/G*k) + b2 >= L

    ll_t lo = ceil( (L - b1 - a1 * X) * G / double( B * a1 ) );
    ll_t hi = floor( (R - b1 - a1 * X) * G / double( B * a1 ) );

    ll_t ans = 0;

    // while( a2 * (Y - A/G*lo) + b2 < L ) lo++;

    while( a1 * (X + B/G*lo) + b1 <= R )
    {
        ll_t l = a2 * (Y - B/G*lo) + b2;
        ll_t r = a1 * (X + B/G*lo) + b1;
        cout << r << ' '<< l << endl;
        lo++;

        if( l >= L && l <= R )
            ans++;
    }

#ifdef LOCAL
    cout << G << ' ' << A << ' ' << B << ' ' << X << ' ' << Y << endl;
    cout << lo << ' ' << hi << endl;
#endif

    // cout << max( ll_t(0), hi - max( ll_t(0), lo ) + 1 ) << endl;

    cout << ans << endl;

    return 0;
}
