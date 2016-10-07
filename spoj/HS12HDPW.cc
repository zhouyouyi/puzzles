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

using namespace std;

int main()
{
    std::ios_base::sync_with_stdio(false);

    int ncase;

    cin >> ncase;

    while(ncase--)
    {
        int N;
        cin >> N;

        vector<string> S(N);
        string P;

        int i, j;

        for(i = 0; i < N; ++i)
            cin >> S[i];

        cin >> P;

        for(i = 0; i < N; ++i)
        {
            int a = 0 , b = 0;

            for(j = 0; j < S[i].size(); ++j)
            {
                a |= ( S[i][j] & (1 << j) );
                b |= ( ((S[i][j] >> ((j+3)%6)) & 1) << j );
            }

            cout << P[a] << P[b];
        }

        cout << endl;
    }

    return 0;
}
