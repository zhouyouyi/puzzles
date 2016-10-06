// C++11

#include <cstdint>
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

uint64_t T[32][256];

int main()
{
    std::ios_base::sync_with_stdio(false);

    string S;

    int idx = 0;

    while(cin >> S)
    {
        if( S == "bye" ) break;

        ++idx;

        memset( T, 0, sizeof(T) );

        int i, j, k;

        for(i = 0; i < S.size(); ++i)
        {
            int num = 0;
            for(j = i; j > 0; --j)
            {
                num += (S[j] - '0');

                for(k = 0; k <= num; ++k)
                    T[i][num] += T[j-1][k];
            }

            num += (S[j] - '0');

            T[i][num] += 1;
        }

#ifdef LOCAL
        for(i = 0; i < S.size(); ++i)
        {
            for(j = 0; j <= 20; ++j)
            {
                cout << setw(3) << T[i][j];
            }
            cout << endl;
        }
#endif

        uint64_t ans = 0;
        for(j = 0; j < 256; ++j)
            ans += T[S.size()-1][j];

        cout << idx << ". " <<  ans << endl;
    }

    return 0;
}
