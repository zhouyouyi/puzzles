#include <iostream>
#include <iomanip>
#include <cstdint>
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

            std::istringstream iss( line );

            string acronym;

            iss >> acronym;

            while( iss >> word )
            {
                if( insig.count( word ) ) continue;

                array.push_back( word );
            }

            int N = acronym.size();
            int M = array.size();

            vector< vector< uint32_t > > T( N+1, vector<uint32_t>( M+1, 0 ) );
        }
    }
    return 0;
}
