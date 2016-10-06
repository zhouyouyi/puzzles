// C++11

// #include <cstdint>
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
#include <cstring>

using namespace std;

const static int32_t Z = (1<<20) + 1;

int64_t T[Z];
int     C[20][20];

int count_bits(int32_t n)
{
   int r = 0;
   while (n > 0) { r += (n&1); n >>= 1; }
   return r;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int ncase;
    cin >> ncase;

    while(ncase--)
    {
        int N;
        cin >> N;

        // vector< vector<int> > C(N, vector<int>(N));

        int i, j;

        for( i = 0; i < N; ++i )
        {
            for( j = 0; j < N; ++j )
            {
                cin >> C[i][j];
            }
        }

        int32_t allmask = (1 << (N)) - 1;

        // vector< vector<int64_t> > T( Z, vector<int64_t>(N, -1) );

        memset( T, 0, sizeof(T) );

        T[allmask] = 1;

        for(j = allmask; j >= 0; --j)
        {
            int32_t idx = count_bits(j);

            for(i = 0; i < N; ++i)
            {
                if( C[idx][i] && (j &(1<<i)) == 0 )
                    T[j] += T[j | (1<<i)];
            }
        }

        cout << T[0] << endl;

    }
    return 0;
}
