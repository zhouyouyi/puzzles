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

typedef unsigned long long ull_t;
typedef long long ll_t;

int main()
{
    int N, K;
    cin >> N >> K;

    vector<int> C(N+1);
    vector<int> V(K+1);
    vector<ull_t> sum_V(K+1, 0);

    int i, j;
    ull_t sum = 0;
    ull_t sum_C = 0;
    ull_t sum_V_square = 0;
    for(i = 1; i <= N; ++i)
    {
        cin >> C[i];

        sum_C += C[i];
    }

    for(i = 1; i <= K; ++i)
    {
        cin >> V[i];

        sum_V_square += (C[V[i]] * C[V[i]]);

        sum_V[i] = (sum_V[i-1] + C[V[i]]);
    }

    vector<bool> done(N+1, false);

    sum = sum_V[K] * sum_C - sum_V_square;

    for(i = 1; i <= K; ++i)
    {
        sum -= ( C[V[i]] * ( sum_V[K] - sum_V[i] ) );

        done[ V[i] ] = true;
    }

    for(i = 1; i < N; ++i)
    {
        if( !done[i] && !done[i+1] )
            sum += (C[i] * C[i+1]);
    }

    if( !done[1] && !done[N] )
        sum += (C[1] * C[N]);

    cout << sum << endl;
    return 0;
}
