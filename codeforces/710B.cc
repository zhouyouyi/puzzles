#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll_t;

int main()
{
    ll_t N;
    cin >> N;
    vector<ll_t> A(N);
    ll_t i;
    for(i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    vector<ll_t> D;
    D.push_back(0);
    for(i = 1; i < N; ++i)
    {
        D.push_back( D.back() + A[i] - A[0] );
    }

    ll_t ans = D.back();
    ll_t pos = 0;

    for(i = 1; i < N; i++)
    {
        ll_t left = (i+1)*(A[i]-A[0]) - D[i];
        ll_t right = D.back() - D[i] - (N-i-1)*(A[i]-A[0]);

        if( left+right < ans )
        {
            ans = left+right;
            pos = i;
        }
    }

    cout << A[pos] << endl;
    return 0;
}
