/*
  ID: zhou.yo1
  PROG: milk
  LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void solve( ifstream& fin, ofstream& out )
{
    int N, M;
    fin >> N >> M;

    int i;
    map<int, int> D;
    for(i = 0; i < M; ++i)
    {
        int price, volume;
        fin >> price >> volume;

        if( D.find(price) == D.end() )
            D[price] = volume;
        else
            D[price] += volume;
    }

    int ans = 0;
    map<int,int>::iterator iter = D.begin();
    map<int,int>::iterator iend = D.end();
    for(; iter != iend; ++iter )
    {
        if( N <= iter->second )
        {
            ans += (iter->first * N );
            break;
        }
        else
        {
            ans += (iter->first * iter->second);
            N -= iter->second;
        }
    }

    out << ans << endl;
}

int main()
{
    ifstream fin("milk.in");
    ofstream out("milk.out");

    solve( fin, out );

    return 0;
}
