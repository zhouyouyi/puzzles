#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cctype>
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

int count_sub( const std::string& sub, int sub_i, int sub_N, const std::string& str, int str_i )
{
    int ans = 0;

    if( sub_i == sub_N ) return 1;

    int i;
    for(i = str_i; i < str.size(); ++i)
    {
        if( str[i] == sub[sub_i] )
            ans += count_sub( sub, sub_i+1, sub_N, str, i+1 );
    }

    return ans;
}

int main()
{
    int W, i, j, k;
    set<string> insig;
    string word;
    string line;

    while( true )
    {
        cin >> W;

        if( W == 0 ) break;

        insig.clear();

        for( i = 0; i < W; ++i )
        {
            cin >> word;

            insig.insert( word );
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while( true )
        {
            std::getline( cin, line );

            if( line == "LAST CASE" ) break;

            vector<string> array;
            array.push_back(""); // dummy

            std::istringstream iss( line );

            string acronym;

            iss >> acronym;

            std::transform( acronym.begin(), acronym.end(), acronym.begin(),
                            [](unsigned char c) { return std::tolower(c); } );

            while( iss >> word )
            {
                if( insig.count( word ) ) continue;

                array.push_back( word );
            }

            int N = acronym.size();
            int M = array.size() - 1;

            vector< vector< uint32_t > > T( N+1, vector<uint32_t>( M+1, 0 ) );

            T[0][0] = 1;

            for(i = 1; i <= N; ++i)
            {
                for(j = 1; j <= M && j <= i; ++j)
                {
                    for(k = 1; k <= i - j + 1; ++k)
                    {
                        if( T[i-k][j-1] != 0 )
                            T[i][j] += (T[i-k][j-1] * count_sub( acronym, i-k, i, array[j], 0 ) );
                    }
                }
            }

            std::transform( acronym.begin(), acronym.end(), acronym.begin(),
                            [](unsigned char c) { return std::toupper(c); } );

            if( T[N][M] )
                cout << acronym << " can be formed in " << T[N][M] << " ways" << endl;
            else
                cout << acronym << " is not a valid abbreviation" << endl;
        }
    }
    return 0;
}
