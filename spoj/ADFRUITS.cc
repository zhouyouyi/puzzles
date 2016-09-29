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
    string S, T;

    while( cin >> S >> T )
    {
        deque<string> R;

        int i, j;

        int LCS[101][101];
        int P[101][101];

        if( S[0] == T[0] )
        {
            LCS[0][0] = 1;
            P[0][0] = 0;
        }
        else
        {
            LCS[0][0] = 0;
            P[0][0] = -1;
        }

        for(i = 1; i < S.size(); ++i)
        {
            if( S[i] == T[0] )
            {
                LCS[i][0] = 1;
                P[i][0] = 0;
            }
            else
            {
                LCS[i][0] = LCS[i-1][0];
                P[i][0] = 2;
            }
        }

        for(j = 1; j < T.size(); ++j)
        {
            if( T[j] == S[0] )
            {
                LCS[0][j] = 1;
                P[0][j] = 0;
            }
            else
            {
                LCS[0][j] = LCS[0][j-1];
                P[0][j] = 1;
            }
        }

        for(i = 1; i < S.size(); ++i)
        {
            for(j = 1; j < T.size(); ++j)
            {
                if( S[i] == T[j] )
                {
                    LCS[i][j] = LCS[i-1][j-1] + 1;

                    P[i][j] = 0;
                }
                else if( LCS[i][j-1] > LCS[i-1][j] )
                {
                    LCS[i][j] = LCS[i][j-1];

                    P[i][j] = 1;
                }
                else
                {
                    LCS[i][j] = LCS[i-1][j];

                    P[i][j] = 2;
                }
            }
        }

        // for( i = 0; i < S.size(); ++i)
        // {
        //     for( j = 0; j < T.size(); ++j )
        //     {
        //         cout << setw(4) << LCS[i][j];
        //     }
        //     cout << endl;
        // }

        int i_start = 0, j_start = 0, i_end = S.size(), j_end = T.size();

        i = S.size() - 1;
        j = T.size() - 1;

        while( i >= 0 && j >= 0 && P[i][j] != -1 )
        {
            switch( P[i][j] )
            {
            case 0:
            {
                if( j_end - j - 1 > 0 )
                    R.push_front( T.substr( j+1, j_end - j - 1 ) );
                if( i_end - i - 1 > 0 )
                    R.push_front( S.substr( i+1, i_end - i - 1 ) );

                R.push_front( S.substr(i, 1) );

                i_end = i;
                j_end = j;

                i--;
                j--;
                break;
            }
            case 1:
            {
                j--;
                break;
            }
            case 2:
            {
                i--;
                break;
            }
            default:
                break;
            }
        }

        if( j_end - j_start > 0 )
            R.push_front( T.substr( j_start, j_end - j_start ) );
        if( i_end - i_start > 0 )
            R.push_front( S.substr( i_start, i_end - i_start ) );

        while( R.size() > 0 )
        {
            cout << R.front();
            R.pop_front();
        }
        cout << endl;
    }
   
    return 0;
}
