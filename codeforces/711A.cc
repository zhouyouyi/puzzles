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

int main()
{
    int N;
    cin >> N;
    vector<string> S(N);
    bool found = false;

    for ( int i = 0; i < N; ++i )
    {
        cin >> S[i];
        string::size_type pos = S[i].find( "OO" );
        if ( !found && pos != string::npos )
        {
            found = true;

            S[i].replace( pos, 2, "++" );
        }
    }

    if ( ! found )
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;

        for ( int i = 0; i < N; ++i )
        {
            cout << S[i] << endl;
        }
    }

    return 0;
}
