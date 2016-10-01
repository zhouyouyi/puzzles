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

int main()
{
    int T;
    cin >> T;

    while(T--)
    {
        int H, W;

        cin >> H >> W;

        vector< vector<int> > T(H, vector<int>( W, 0 ) );

        int i, j;

        int ans = 0;

        for(j = 0; j < W; ++j)
        {
            cin >> T[0][j];

            ans = max(ans, T[0][j]);
        }

        for(i = 1; i < H; ++i)
        {
            for(j = 0; j < W; ++j)
            {
                cin >> T[i][j];

                int k = T[i-1][j];

                if( j - 1 >= 0 ) k = max( k, T[i-1][j-1] );
                if( j + 1 <= W-1 ) k = max( k, T[i-1][j+1] );

                T[i][j] += k;

                ans = max(ans, T[i][j]);
            }
        }

        cout << ans << endl;
    }
    return 0;
}
