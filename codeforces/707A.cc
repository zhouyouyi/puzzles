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
    int n, m;
    int C = 0, M = 0, Y = 0, W = 0, G = 0, B = 0;

    int i, j;

    cin >> n >> m;

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            string s;

            cin >> s;

            switch(s[0])
            {
                case 'C': C++; break;
                case 'M': M++; break;
                case 'Y': Y++; break;
                case 'W': W++; break;
                case 'G': G++; break;
                case 'B': B++; break;
                default: break;
            }
        }
    }

    if(C == 0 && M == 0 && Y == 0)
        cout << "#Black&White" << endl;
    else
        cout << "#Color" << endl;
    return 0;
}
