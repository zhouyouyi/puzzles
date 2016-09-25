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
    string S;

    int i, N;

    vector<ull_t> T(5001, 0);

    while( cin >> S )
    {
        if ( S == "0" ) break;

        // T[0] = 1;

        N = S.size();

        std::fill( T.begin(), T.end(), 0 );

        if( S[0] >= '1' && S[0] <= '9' ) T[1] = 1;
        if( N > 1 )
        {
            if( S[1] >= '1' && S[1] <= '9' ) T[2] = 1;

            int c = ( (S[0]-'0') * 10 + (S[1]-'0') );

            if( c >= 1 && c <= 26 )
                T[2] += 1;
        }

        for(i = 3; i <= N; ++i)
        {
            T[i] = 0;
            if( S[i-1] >= '1' && S[i-1] <= '9' )
                T[i] += T[i-1];

            if( i-1 > 0 && S[i-2] != '0' )
            {
                int c = ( (S[i-2]-'0') * 10 + (S[i-1]-'0') );

                if( c >= 1 && c <= 26 )
                    T[i] += T[i-2];
            }

            if( T[i] == 0 ) break;
        }

        cout << T[N] << endl;
    }
    return 0;
}
