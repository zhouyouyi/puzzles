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
#include <unordered_map>
#include <cstdint>

using namespace std;

unordered_map<uint64_t, uint64_t> T;

uint64_t find_max( uint64_t n )
{
    if( T.find(n) != T.end() ) return T[n];

    T[n] = max( n, find_max(n/2) + find_max(n/3) + find_max(n/4) );

    return T[n];
}

int main()
{
    uint64_t n;

    T[0] = 0;
    T[1] = 1;
    T[2] = 2;
    T[3] = 3;
    T[4] = 4;

    while( cin >> n )
    {
        cout << find_max(n) << endl;
    }
    return 0;
}
