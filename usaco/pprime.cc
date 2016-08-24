/*
  ID: zhou.yo1
  PROG: pprime
  LANG: C++
*/

#define PROG "pprime"

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

vector<bool> primes;

// bool primes[1000000000+1] = {true};

void gen_primes( long n )
{
    // primes.resize( n+1, true );
    primes[0] = primes[1] = false;

    long i;
    for(i = 2; i < long(sqrt(n)) + 1; ++i)
    {
        if( primes[i] )
        {
            for(long j = i*i; j <= n; j += i)
                primes[j] = false;
        }
    }
}

int numlen( long n )
{
    int l = 0;
    while(n) { l++; n/=10; }
    return l;
}

bool is_prime( long n )
{
    for(long i = 2; i < long(sqrt(n))+1; ++i)
    {
        if( n % i == 0 ) return false;
    }

    return true;
}

void gen_pal(vector<int>& digits, int l, int cur, ostream& out, long A, long B)
{
    if( cur == l/2 )
    {
        long hi = 0;

        for(int i = 0; i < digits.size(); ++i)
        {
            hi = hi*10 + digits[i];
        }

        long lo = 0;

        for(int i = digits.size()-1; i >= 0; --i)
        {
            hi = hi * 10;
            lo = lo*10 + digits[i];
        }

        if( l % 2 == 1 )
        {
            for(int d = 0; d <= 9; ++d)
            {
                long pal = hi*10 + d * pow(10,l/2) + lo;

                // cout << pal << endl;

                if( pal >= A && pal <= B && is_prime(pal) )
                    out << pal << endl;
            }
        }
        else
        {
            long pal = hi + lo;

            // cout << pal << endl;

            if( pal >= A && pal <= B && is_prime(pal) )
                out << pal << endl;
        }
    }
    else
    {
        int i = (cur == 0 ? 1 : 0);
        for(; i <= 9; ++i)
        {
            digits.push_back(i);
            gen_pal( digits, l, cur+1, out, A, B );
            digits.pop_back();
        }
    }
}

void solve( istream& fin, ostream& out )
{
    long A, B;
    fin >> A >> B;

    // gen_primes( B );

    int len_a = numlen(A);
    int len_b = numlen(B);

    int l;
    for(l = len_a; l <= len_b; ++l)
    {
        vector<int> digits;

        gen_pal( digits, l, 0, out, A, B );
    }
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
