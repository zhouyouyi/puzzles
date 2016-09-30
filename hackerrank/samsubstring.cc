#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <cmath>
#include <string>
using namespace std;

// typedef unsigned long long uint64_t;

const static uint64_t inf = std::numeric_limits<uint64_t>::max();
const static uint64_t MOD = 1E9L + 7L;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    std::ios_base::sync_with_stdio(false);
    string S;
    cin >> S;
    int N = S.size();
    
    uint64_t T = S[0] - '0';
    uint64_t D = S[0] - '0';
    
    int i;
    for(i = 2; i <= N; ++i)
    {
        uint64_t num = S[i-1] - '0';
        
        D = ( D * 10 + (i*num) % MOD ) % MOD;

        T = ( D + T ) % MOD;
    }
    
    cout << T << endl;
    return 0;
}
