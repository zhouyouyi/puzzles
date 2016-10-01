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
        string S;

        cin >> S;

        int N = S.size();

        int i, j;

        vector< vector<int> > LCS(N, vector<int>(N, 0));

        LCS[0][0] = ( S[0] == S[N-1] );

        for(i = 1; i < N; ++i)
        {
            if( S[i] == S[N-1] )
                LCS[i][0] = 1;
            else
                LCS[i][0] = LCS[i-1][0];
        }

        for(j = 1; j < N; ++j)
        {
            if( S[N-j-1] == S[0] )
                LCS[0][j] = 1;
            else
                LCS[0][j] = LCS[0][j-1];
        }
        
        for(i = 1; i < N; ++i)
        {
            for(j = 1; j < N; ++j)
            {
                if( S[i] == S[N-j-1] )
                {
                    LCS[i][j] = LCS[i-1][j-1] + 1;
                }
                else if( LCS[i-1][j] > LCS[i][j-1] )
                {
                    LCS[i][j] = LCS[i-1][j];
                }
                else
                {
                    LCS[i][j] = LCS[i][j-1];
                }
            }
        }

        cout << N - LCS[N-1][N-1] << endl;
    }
    return 0;
}
