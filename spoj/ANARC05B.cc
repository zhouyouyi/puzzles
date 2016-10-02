#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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
    while(true)
    {
        int LA, LB;
        cin >> LA;

        if(LA == 0) break;

        int i, j;

        vector<int> A(LA, 0);

        for(i = 0; i < LA; ++i)
            cin >> A[i];

        cin >> LB;

        vector<int> B(LB, 0);

        for(j = 0; j < LB; ++j)
            cin >> B[j];

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        // vector<int> TA(LA+1, 0), TB(LB+1, 0);
        long long TA = 0, TB = 0;

        i = 0, j = 0;

        while( i < LA )
        {
            vector<int>::iterator it = lower_bound( B.begin() + j, B.end(), A[i] );

            if( it == B.end() || *it != A[i] )
            {
                TA = A[i] + TA;
                ++i;
            }
            else
            {
                while( j < (it - B.begin()) )
                {
                    TB = B[j] + TB;

                    ++j;
                }

                TA = TB = max( TA, TB ) + A[i];
                
                ++i;
                ++j;
            }
        }

        while( j < LB )
        {
            TB = TB + B[j];
            ++j;
        }

        cout << max( TA, TB ) << endl;
    }

    return 0;
}
