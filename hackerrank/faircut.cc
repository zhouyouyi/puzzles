#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

static const int64_t inf = std::numeric_limits<int64_t>::max();

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, K;
    cin >> N >> K;
    
    if( K > N / 2) K = N - K;
    
    vector<int64_t> A(N);
    vector< vector<int64_t> > T(N+1, vector<int64_t>(N+1, inf));
    int i, j;
    
    T[0][0] = 0;
    
    for(i = 0; i < N; ++i)
        cin >> A[i];
    
    sort(A.begin(), A.end());
    
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j <= i; ++j)
        {
            if(j > K || i - j > N - K) continue;
            
            int64_t li = T[i][j] + A[i] * (i - j - (N - K - (i - j)));
            
            int64_t lu = T[i][j] + A[i] * (j - (K - j));
            
            if(T[i+1][j+1] > li)
                T[i+1][j+1] = li;
            
            if(T[i+1][j] > lu)
                T[i+1][j] = lu;
        }
    }
    
    cout << T[N][K] << endl;
    return 0;
}
