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

const static uint64_t MOD = 1E9L + 7L;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    std::ios_base::sync_with_stdio(false);
    string S;
    cin >> S;
    int N = S.size();
    
    vector<uint64_t> T(N+1, 0);
    vector<uint64_t> D(N+1, 0);
    
    T[0] = 0;
    T[1] = S[0] - '0';

    D[0] = 0;
    D[1] = S[0] - '0';
    
    int i;
    for(i = 2; i <= N; ++i)
    {
        uint64_t num = S[i-1] - '0';
        
        D[i] = ( D[i-1]*10 + (i*num) % MOD ) % MOD;

        T[i] = ( D[i] + T[i-1] ) % MOD;
    }
    
    cout << T[N] << endl;
    return 0;
}
