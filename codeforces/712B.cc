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
    cin >> S;

    map<char, int> C;
    C['L'] = C['R'] = C['U'] = C['D'] = 0;

    int N = S.size();
    int i;
    for( i = 0; i < N; ++i )
    {
        C[S[i]]++;
    }

    if ( N % 2 == 1 )
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ( std::abs(C['L'] - C['R']) + std::abs( C['U'] - C['D'] ) ) / 2 << endl;
    }

    return 0;
}
