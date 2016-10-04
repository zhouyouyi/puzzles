#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string S, T;
    
    cin >> S >> T;
    
    int N = S.size(), M = T.size();
        
    vector< vector<int> > L(S.size(), vector<int>(T.size(), 0));
    vector< vector<int> > R(S.size(), vector<int>(T.size(), 0));
    
    vector< vector<bool> > F(N+1, vector<bool>(255, false));
    
    int i, j, ans = 0;
    
    L[0][0] = (S[0] == T[0]);
    R[N-1][M-1] = (S[N-1] == T[M-1]);
    
    for(i = 1; i < N; ++i)
    {
        if(S[i] == T[0]) L[i][0] = 1;
        else L[i][0] = L[i-1][0];
        
        if(S[N-1-i] == T[M-1]) R[N-1-i][M-1] = 1;
        else R[N-1-i][M-1] = R[N-i][M-1];
    }
    
    for(j = 1; j < M; ++j)
    {
        if(S[0] == T[j]) L[0][j] = 1;
        else L[0][j] = L[0][j-1];
        
        if(S[N-1] == T[M-1-j]) R[N-1][M-1-j] = 1;
        else R[N-1][M-1-j] = R[N-1][M-j];
    }
    
    for(i = 1; i < N; ++i)
    {
        for(j = 1; j < M; ++j)
        {
            if(S[i] == T[j])
            {
                L[i][j] = L[i-1][j-1] + 1;
            }
            else
            {
                L[i][j] = max(L[i-1][j], L[i][j-1]);
            }
            
            if(S[N-1-i] == T[M-1-j])
            {
                R[N-1-i][M-1-j] = R[N-i][M-j] + 1;
            }
            else
            {
                R[N-1-i][M-1-j] = max(R[N-i][M-1-j], R[N-1-i][M-j]);
            }
        }
    }
    
    for(i = 0; i <= N; ++i)
    {
        for(j = 0; j < M; ++j)
        {
            if(! F[i][T[j]])
            {
                int left = (i-1 >= 0 && j-1 >= 0 ? L[i-1][j-1] : 0);
                int right = (i < N && j+1 < M ? R[i][j+1] : 0);
                
                if(left + right == L[N-1][M-1])
                {
                    ans++;
                    F[i][T[j]] = true;
                }
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
