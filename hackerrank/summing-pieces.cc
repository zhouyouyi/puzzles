#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const static uint64_t MOD = 1E9L + 7L;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin >> N;
    
    uint64_t A;
    
    cin >> A;
    
    uint64_t T = A;
    uint64_t S = A;
    uint64_t P = 0;
    
    uint64_t Q = 1; // power of 2
    
    for(int i = 2; i <= N; ++i)
    {
        cin >> A;
        
        P = (P + ((Q * S) % MOD)) % MOD;
        //cerr << "P[" << i << "] = " << P << endl;
        Q = (Q * 2) % MOD;
        //cerr << "Q[" << i << "] = " << Q << endl;
        S = (S + A) % MOD;
        //cerr << "S[" << i << "] = " << S << endl;
        T = (((2*T) % MOD + ((Q * S) % MOD)) % MOD);
        T = (T + (((Q-1) * A) % MOD) + MOD - P) % MOD;
        //cerr << "T[" << i << "] = " << T << endl;
    }
    cout << T << endl;
    return 0;
}
