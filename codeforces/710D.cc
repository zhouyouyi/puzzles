#include <iostream>
#include <cmath>
#include <iomanip>

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
    else
    {
        g = gcd_ext( b, a%b, x, y );
        t = x;
        x = y;
        y = t - a/b*y;

        return g;
    }
}

int main()
{
    long long a1, b1, a2, b2, L, R;
    cin >> a1 >> b1 >> a2 >> b2 >> L >> R;

    ll_t A = a1;
    ll_t B = a2;
    ll_t C = b2 - b1;

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
    ll_t ans = 0;

    // ll_t K = (ll_t)max( ceil(Y*G/double(A)), ceil(-X*G/double(B)) );

    // ll_t S = a1 * (X + B*K/G) + b1;
    // ll_t T = a2 * (Y - A*K/G) + b2;

    // cap the minimum K value to ensure k and l >= 0
    ll_t K = (ll_t)max( ceill(-X*G/double(B)), ceill(Y*G/double(A)) );
    ll_t U = (ll_t)floorl( (R - b1 - a1 * X) * G / double( B * a1 ) + 0.00001 );

#ifdef LOCAL
    cout << std::fixed;
    cout << G << ' ' << A << ' ' << B << ' ' << X << ' ' << Y << endl;

    cout << "LOWER " << (L - b1 - a1 * X) * G / double( B * a1 )
         << " " <<  (L - b2 + a2 * Y) * G / double( A * a2 )
         << " K " << -X*G/double(B)
         << " U " << U
         << " K " << K
         << endl;

    cout << "UPPER " << (R - b1 - a1 * X) * G / double( B * a1 )
         << " " <<  (R - b2 + a2 * Y) * G / double( A * a2 )
         << " K " << Y*G/double(A)
         << " U " << U
         << " K " << K
         << endl;

    cout << "S " << a1 * (X + (B/G)*K) + b1
         << " T " << a2 * (-Y + (A/G)*K) + b2
         << endl;
#endif

    // cap the minimum K to ensure a1*x + b1 falls in [L, R]
    K = (ll_t) max( ceill( (L - b1 - a1 * X) * G / double( B * a1 ) ), (long double)(K) );

    while( K <= U )
    {
        ll_t S = a1 * (X + (B/G)*K) + b1;
        ll_t T = a2 * (-Y + (A/G)*K) + b2;

        cout << "S " << S << " T " << T << endl;

        K++;
    }
#ifdef LOCAL
    cout 
         << " U " << U
         << " K " << K
         << " S " << a1 * (X + (B/G)*K) + b1
         << " R " << R
         << "   " << (ll_t(a1 * (X + (B/G)*K) + b1) > R)
         << endl;
#endif

    // negative answer means no available choices
    cout << max( ll_t(0), ans ) << endl;

    return 0;
}
