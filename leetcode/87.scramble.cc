#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        int len1 = s1.size();
        if(len1 == 0) return true;
        if(len1 == 1) return s1 == s2;
        
        bool DP[len1+1][len1][len1];
        
        int i, j, k, t;
        for(i = 0; i < len1; ++i)
        {
            for(j = 0; j < len1; ++j)
            {
                DP[1][i][j] = (s1[i] == s2[j]);
            }
        }
        
        for(t = 2; t <= len1; ++t)
        {
            for(i = 0; i <= len1 - t; ++i)
            {
                for(j = 0; j <= len1 - t; ++j)
                {
                    DP[t][i][j] = false;
                    
                    for(k = 1; k < t && !DP[t][i][j]; ++k)
                    {
                        DP[t][i][j] = DP[t][i][j] || (DP[k][i][j] && DP[t-k][i+k][j+k]);
                        DP[t][i][j] = DP[t][i][j] || (DP[k][i+t-k][j] && DP[t-k][i][j+k]);
                    }
                }
            }
        }
        
        return DP[len1][0][0];
    }
};

int main()
{
    string s, t;

    Solution sol;

    while( cin >> s >> t )
    {
        cout << sol.isScramble( s, t ) << endl;
    }

    return 0;
}
