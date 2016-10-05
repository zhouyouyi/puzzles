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
    string S;
    int id = 0;

    while(cin >> S)
    {
        if(S[0] == '-') break;

        id++;

        int ans = 0;

        deque<char> st;

        for( int i = 0; i < S.size(); ++i )
        {
            if( S[i] == '{' )
                st.push_back(S[i]);
            else if( S[i] == '}' )
            {
                if( st.empty() )
                {
                    ans++;
                    st.push_back( '{' );
                }
                else
                {
                    st.pop_back();
                }
            }
        }

        ans += (st.size() / 2);

        cout << id << ". " << ans << endl;
    }
    return 0;
}
