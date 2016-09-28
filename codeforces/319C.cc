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

struct line_t
{
    ll_t k;
    ll_t b;

    double x0;

    line_t() : k(0), b(0), x0( std::numeric_limits<double>::min() ) {}

    double intersect( const line_t& other ) const
    {
        return double(b - other.b) / (other.k - k);
    }

    ll_t y_at( const ll_t x ) const { return k*x + b; }
};

int main()
{
    int N;

    cin >> N;

    int i;
    vector<ll_t> A(N+1);
    vector<ll_t> B(N+1);

    vector<line_t> Q;

    ll_t T = 0;

    for(i = 1; i <= N; ++i)
    {
        cin >> A[i];
    }

    for(i = 1; i <= N; ++i)
    {
        cin >> B[i];
    }

    int pos = 0;

    for(i = 2; i <= N; ++i)
    {
        line_t l;
        l.k = B[i-1];
        l.b = T;

        Q.push_back(l);

        while( Q.size() > 2 )
        {
            line_t& l3 = Q[Q.size()-1];
            line_t& l2 = Q[Q.size()-2];
            line_t& l1 = Q[Q.size()-3];

            if( l3.intersect(l1) <= l2.intersect(l1) )
            {
                l2 = l3;
                Q.pop_back();

                if( pos == Q.size() ) --pos;
            }
            else
            {
                break;
            }
        }

        if( Q.size() > 1 )
        {
            Q.back().x0 = Q.back().intersect( Q[Q.size()-2] );
        }

        while( pos + 1 < Q.size() && Q[pos+1].x0 < A[i] ) ++pos;

        T = Q[pos].y_at(A[i]);
    }

    cout << T << endl;
    return 0;
}
