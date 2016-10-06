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

int LCS[2001][2001];

int main()
{
    std::ios_base::sync_with_stdio(false);

    int ncase;

    cin >> ncase;

    vector<int> agness;
    vector<int> tom;

    int i, j, n;

    while(ncase--)
    {
        agness.clear();

        while(cin >> n)
        {
            if( n == 0 ) break;

            agness.push_back(n);
        }

        int ans = 0;
        while(true)
        {
            tom.clear();

            while(cin >> n)
            {
                if( n == 0 ) break;

                tom.push_back(n);
            }

            if( n == 0 && tom.empty() ) break;

            memset( LCS, 0, sizeof(LCS) );

            LCS[0][0] = ( agness[0] == tom[0] );

            for(i = 1; i < agness.size(); ++i)
            {
                if( agness[i] == tom[0] ) LCS[i][0] = 1;
                else LCS[i][0] = LCS[i-1][0];
            }

            for(j = 1; j < tom.size(); ++j)
            {
                if( tom[j] == agness[0] ) LCS[0][j] = 1;
                else LCS[0][j] = LCS[0][j-1];
            }

            for(i = 1; i < agness.size(); ++i)
            {
                for(j = 1; j < tom.size(); ++j)
                {
                    if( agness[i] == tom[j] )
                    {
                        LCS[i][j] = LCS[i-1][j-1] + 1;
                    }
                    else
                    {
                        LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1]);
                    }
                }
            }

            // for(i = 0; i < agness.size(); ++i)
            // {
            //     for(j = 0; j < tom.size(); ++j)
            //     {
            //         cout << setw(4) << LCS[i][j];
            //     }
            //     cout << endl;
            // }

            ans = max(ans, LCS[agness.size()-1][tom.size()-1]);
        }

        cout << ans << endl;
    }

    return 0;
}
