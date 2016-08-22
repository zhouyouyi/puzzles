#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool solve(vector<int>& P, int num, int term, int k)
{
    if(num == term)
    {
        for(int i = 1; i < P.size(); i++)
            cout << P[i] << ' ';
        cout << endl;
        return true;
    }
    
    if(num + k < P.size() && P[num+k] == 0)
    {
        P[num+k] = num;
        
        if( solve(P, num+1, term, k) ) return true;
        
        P[num+k] = 0;
    }
    
    if(num - k > 0 && P[num-k] == 0)
    {
        P[num-k] = num;
        
        if( solve(P, num+1, term, k) ) return true;
        
        P[num-k] = 0;
    }
    
    return false;
}

int main(){
    int T;
    cin >> T;
    while(T--)
    {
        int N, K;
        cin >> N >> K;

        if( 2 * K > N )
        {
            cout << -1 << endl;
            continue;
        }
        
        vector<int> p(N+1, 0);

        int i;
        for( i = 1; i <= K; ++i )
        {
            p[i+K] = i;
        }

        bool valid = true;
        for( i = N; i > N - K; --i )
        {
            if( p[i-K] != 0 )
            {
                valid = false;
                break;
            }

            p[i-K] = i;
        }

        if( !valid )
        {
            cout << -1 << endl;
            continue;
        }
        
        if(!solve(p, K+1, N-K+1, K))
            cout << -1 << endl;
    }
    return 0;
}
