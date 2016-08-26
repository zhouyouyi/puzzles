/*
  ID: zhou.yo1
  PROG: frac1
  LANG: C++
*/

#define PROG "frac1"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

struct frac_t
{
    frac_t(){}
    frac_t(int f, int d) : frac(f), denom(d) {}
    int frac;
    int denom;

    void norm() { int g = gcd(frac, denom); frac /= g; denom /= g; }
};

bool GT(const frac_t& a, const frac_t& b)
{
    return a.frac * b.denom > a.denom * b.frac;
}

bool EQ(const frac_t& a, const frac_t& b)
{
    return a.frac * b.denom == a.denom * b.frac;
}

void solve( istream& fin, ostream& out )
{
    int N;
    fin >> N;

    vector< frac_t > H;

    int i;
    for(i = 0; i < N; ++i)
    {
        H.push_back( frac_t(1, i+1) );
    }

    out << "0/1" << endl;

    make_heap( H.begin(), H.end(), GT );

    frac_t last_frac(0,1);

    while( H.size() > 0 )
    {
        frac_t f = H.front();

        pop_heap(H.begin(), H.end(), GT);

        if( ! EQ(last_frac, f) )
        {
            f.norm();
            out << f.frac << "/" << f.denom << endl;
        }

        last_frac = f;

        if( H.back().frac < H.back().denom - 1 )
        {
            H.back().frac++;
            push_heap(H.begin(), H.end(), GT);
        }
        else
        {
            H.pop_back();
        }
    }
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

#ifdef LOCAL
  solve( cin, cout );
#else
  solve( fin, out );
#endif

  return 0;
}
