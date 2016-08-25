/*
  ID: zhou.yo1
  PROG: sprime
  LANG: C++
*/

#define PROG "sprime"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

bool is_prime( int n )
{
    for(int i = 2; i < int(sqrt(n))+1; ++i)
    {
        if( n % i == 0 ) return false;
    }

    return true;
}

void gen_prime( int p, int l, int n, ostream& out )
{
    if( l == n )
    {
        out << p << endl;
        return;
    }

    int i;
    for( i = (l == 0 ? 2 : 1); i <=9; ++i )
    {
        int k = p*10 + i;

        if( is_prime( k ) )
        {
            gen_prime( k, l+1, n, out );
        }
    }
}

void solve( istream& fin, ostream& out )
{
    int N;
    fin >> N;

    gen_prime( 0, 0, N, out );
}

int main()
{
  ofstream out( PROG ".out");
  ifstream fin( PROG ".in");

#ifdef LOCAL
  solve( cin, cout );
#else
  solve( fin, out );
#endif

  return 0;
}
