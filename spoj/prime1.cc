#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

set<long> cache;

bool is_prime( long N )
{
    if( N < 2 ) return false;

    if( cache.find( N ) != cache.end() ) return true;
    
    long i;
    for(i = 2; i <= sqrt(N); ++i)
    {
        if( N % i == 0 ) return false;
    }

    cache.insert( N );

    return true;
}

int main()
{
    int T;
    cin >> T;
    int t;
    vector<long> A(T), B(T);
    long N = 0;
    for( t = 0; t < T; ++t )
    {
        cin >> A[t] >> B[t];
        N = max( N, B[t] );
    }

    long P;

    for( t = 0; t < T; ++t )
    {
        for(P = A[t]; P <= B[t]; ++P)
        {
            if( is_prime(P) )
                cout << P << endl;
        }
        cout << endl;
    }

    return 0;
}
