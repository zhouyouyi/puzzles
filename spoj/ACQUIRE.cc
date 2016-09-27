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

const static ull_t inf = std::numeric_limits<ull_t>::max();

struct plot_t
{
    int w;
    int h;

    plot_t() {}
    plot_t(int ww, int hh) : w(ww), h(hh) {}

    bool operator < ( const plot_t& p ) const
    {
        return h < p.h || (h == p.h && w > p.w);
    }
};

int main()
{
    int N, i, j;

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

    vector<ull_t> T(N+1, 0);

    for(i = 1; i <= N; ++i)
    {
        T[i] = inf;

        for(j = 0; j < i; ++j)
            T[i] = min( T[i], ull_t( T[j] + P[j].w * P[i-1].h ) );
    }

    cout << T[N] << endl;
    
    return 0;
}
