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

typedef unsigned long long ull_t;
typedef long long ll_t;

const static ll_t inf = std::numeric_limits<ll_t>::max();

struct plot_t
{
    ll_t w;
    ll_t h;

    plot_t() {}
    plot_t(ll_t ww, ll_t hh) : w(ww), h(hh) {}

    bool operator < ( const plot_t& p ) const
    {
        return h < p.h || (h == p.h && w > p.w);
    }
};

// a line takes form of y = k*x + b
struct line_t
{
    ll_t k;
    ll_t b;

    double x0; // the intersection point with the previous line

    line_t() {}

    line_t( ll_t kk, ll_t bb ) : k(kk), b(bb), x0( std::numeric_limits<double>::min() ) {}

    double intersect( const line_t& other ) const
    {
        return double(other.b - b) / (k - other.k);
    }

    bool is_parallel( const line_t& other ) const
    {
        return k == other.k;
    }

    ll_t y_at( ll_t x ) const
    {
        return k*x+b;
    }
};

struct x0_less_t
{
    bool operator () ( const line_t& a, const line_t& b ) const
    {
        return a.x0 < b.x0;
    }
};

int main()
{
    int N, i;

    x0_less_t x0_less;

    cin >> N;

    vector<plot_t> V(N);

    for(i = 0; i < N; ++i)
    {
        cin >> V[i].w >> V[i].h;
    }

    sort( V.begin(), V.end() );

    vector<plot_t> P;

    P.push_back( V.front() );

    for(i = 1; i < N; ++i)
    {
        while( P.size() > 0 && P.back().w <= V[i].w ) P.pop_back();

        P.push_back( V[i] );
    }

    V.clear();

    vector<ll_t> T(N+1, 0);

    vector<line_t> Q;

    for(i = 1; i <= N; ++i)
    {
        line_t l3(P[i-1].w, T[i-1]);

        while( Q.size() > 1 )
        {
            line_t l2 = Q.back();
            Q.pop_back();

            if( l3.is_parallel( l2 ) )
            {
                if( l3.b >= l2.b )
                {
                    l3 = l2;
                }
            }
            else
            {
                line_t& l1 = Q.back();

                if( l3.intersect(l1) > l2.x0 )
                {
                    Q.push_back(l2);
                }
            }
        }

        if( Q.size() > 0 )
            l3.x0 = l3.intersect( Q.back() );

        Q.push_back(l3);

        line_t xl(0,0);
        xl.x0 = P[i-1].h;

        vector<line_t>::iterator it = std::lower_bound( Q.begin(), Q.end(), xl, x0_less );

        if( it == Q.end() ) --it;

        T[i] = it->y_at( P[i-1].h );
    }

    cout << T[N] << endl;
    
    return 0;
}
